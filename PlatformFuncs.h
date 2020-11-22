#pragma once
#include "Platform.h"

void initPlatform();
void attachPlatform(PlatformPtr& elem, const PlatformPtr& prev);
void movingPlatform();
void reInitGame();