/*  Copyright 2016 devMiyax(smiyaxdev@gmail.com)

    This file is part of Yabause.

    Yabause is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Yabause is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Yabause; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "yabause.h"
#include "frameprofile.h"
#include "osdcore.h"
#ifdef WIN32
#include <windows.h>
#endif
#ifdef _VDP_PROFILE_
#include "time.h"
#include "threads.h"

// rendering performance
typedef struct {
	char event[32];
	u32 time;
	u32 tid;
} ProfileInfo;

#define MAX_PROFILE_COUNT (256)
ProfileInfo g_pf[MAX_PROFILE_COUNT];
u32 current_profile_index = 0;


void FrameProfileInit(){
	current_profile_index = 0;
}

void FrameProfileAdd(char * p){
	u32 time;
	if (current_profile_index >= MAX_PROFILE_COUNT) return;

#ifdef WIN32
	static LARGE_INTEGER freq = { 0 };
	u64 ticks;
	if (freq.QuadPart == 0){
		QueryPerformanceFrequency(&freq);
	}
	QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
	ticks = ticks * 1000000L / freq.QuadPart;
	time = ticks;
#else
	time = clock();
#endif
	sprintf(g_pf[current_profile_index].event, "%s(%d)",p,YabThreadGetCurrentThreadAffinityMask());
	g_pf[current_profile_index].time = time;
	g_pf[current_profile_index].tid = YabThreadGetCurrentThreadAffinityMask();
	current_profile_index++;
}


void FrameProfileShow(){
	u32 intime = 0;
	u32 extime = 0;
	int i = 0;
	if (current_profile_index <= 0) return;
	for ( i = 0; i < current_profile_index; i++){
		if (i > 0){
			intime = g_pf[i].time - g_pf[i - 1].time;
			extime += intime;
		}
		OSDAddFrameProfileData(g_pf[i].event, intime);
	}
}
#endif
