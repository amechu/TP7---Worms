#pragma once

enum events { REFRESH, REFRESHLEFT, REFRESHRIGHT, LEFT, RIGHT, TOGGLE, JUMP, QUIT, NOEVENT };
enum fromRefresh {EVENT_DRIVEN, REFRESH_DRIVEN};

struct Event {
	unsigned int type;
	unsigned int id;
};
