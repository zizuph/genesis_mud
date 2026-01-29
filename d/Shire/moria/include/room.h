/* Room specific things */

#ifndef _ROGON_ROOM_H_
#define _ROGON_ROOM_H_

#define EXIT(where,dir) add_exit(THIS_DIR+where,dir,0)
#define NORTH(where) add_exit(THIS_DIR+where,"north",0)
#define EAST(where) add_exit(THIS_DIR+where,"east",0)
#define WEST(where) add_exit(THIS_DIR+where,"west",0)
#define SOUTH(where) add_exit(THIS_DIR+where,"south",0)
#define UP(where) add_exit(THIS_DIR+where,"up",0)
#define DOWN(where) add_exit(THIS_DIR+where,"down",0)

#define NORTHEAST(where) add_exit(THIS_DIR+where,"northeast",0)
#define SOUTHEAST(where) add_exit(THIS_DIR+where,"southeast",0)
#define NORTHWEST(where) add_exit(THIS_DIR+where,"northwest",0)
#define SOUTHWEST(where) add_exit(THIS_DIR+where,"southwest",0)

#define ITEM(what,desc) add_item(what,desc)
#define CMD_ITEM(what,how,desc) add_cmd_item(what,how,desc)

#endif
