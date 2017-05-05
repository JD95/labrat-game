#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "../../labrat/entity/entity.h"
#include "../../labrat/scene/SceneState.h"
#include "../../labrat/scene/camera.h"
#include "../../labrat/scene/scene.h"
#include "../../labrat/reactive/reactive.h"
#include "../../labrat/reactive/source.h"

struct VoiceClips {

	const double wait_period = 10000.0;

	double clip_timer;
	double wait_timer;
	double current_clip_length;
	size_t current_track;
	bool intro_done;

	Reactive<SoundClips<2>> intro_clips;
	Reactive<SoundClips<11>> malaphor_clips;
	Reactive<SoundClips<33>> witty_clips;

	std::vector<Sound*> playlist;

	std::random_device rd;
	std::mt19937 g;

	VoiceClips(Reactive<SoundClips<2>>& i, Reactive<SoundClips<11>>& m, Reactive<SoundClips<33>>& w)
		: intro_done(false)
		, clip_timer(0)
		, current_clip_length(0)
		, wait_timer(0)
		, current_track(0)
		, intro_clips(i)
		, malaphor_clips(m)
		, witty_clips(w)
		, g(rd())
	{
		playlist.push_back(intro_clips.value[0]);
		playlist.push_back(intro_clips.value[1]);
		current_clip_length = intro_clips.value[0]->length();
		playlist[current_track]->play();
	}

	auto random_playlist() {
		std::vector<Sound*> rand;
		rand.insert(rand.end(), malaphor_clips.value.begin(), malaphor_clips.value.end());
		rand.insert(rand.end(), witty_clips.value.begin(), witty_clips.value.end());
		std::shuffle(rand.begin(), rand.end(), g);
		return rand;
	}

	auto operator()(Reactive<std::chrono::nanoseconds>& delta_time){
		return from(delta_time)
			.use([this](std::chrono::nanoseconds dt) {
				std::cout << clip_timer << "\n";
				clip_timer += dt.count() * 0.000001;
				//std::cout << clip_timer << "\n";
				// Clip over
				if (clip_timer > current_clip_length + intro_done ? wait_period : 0) {
					current_track++;
					clip_timer = 0;

					// Next Track
					if (current_track < playlist.size()) {
						current_clip_length = playlist[current_track]->length();
					}
					else {
						if (!intro_done) intro_done = true;
						playlist = random_playlist();
						current_track = 0;
					}

					playlist[current_track]->play();
				}

				return dt;
				
		}).determine(delta_time);
	}

};