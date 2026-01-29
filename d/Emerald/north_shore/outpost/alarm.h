#ifndef OUTPOST_ALARM_DEFS
#define OUTPOST_ALARM_DEFS

#include "defs.h"

#define ALARM_OBJECT     (OUTPOST1_DIR + "alarm")
#define ALARM_ENEMIES    (ALARM_OBJECT->query_enemies())
#define ALARM_ACTIVATE   (ALARM_OBJECT->active_alarm())
#define ALARM_DEACTIVATE (ALARM_OBJECT->deactive_alarm())
#define ALARM_NOTIFY     (ALARM_OBJECT->add_notify(this_object()))
#define ALARM_ENEMY(ob)  (ALARM_OBJECT->query_enemy(ob))

#endif

