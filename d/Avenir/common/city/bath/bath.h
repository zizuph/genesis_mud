// bath.h
#ifndef __AVE_BATH_H__
#define __AVE_BATH_H__

#define DEBUG
#ifdef DEBUG
# define DBG(x)	find_player("lucius")->catch_tell("BATH: "+ x +"\n")
#endif

#include "../city.h"

#define BATHRM		(BATH + "room/")
#define BATHOB		(BATH + "obj/")
#define BATH_ROOM	(BATH + "bath")
#define BATH_PRIV	(BATH + "priv")

#define PRIV_KEY_ID	"_melchoir_bath_key"
#define PRIV_DOOR_ID	"_avenir_bath_private_"

#define MNGR		(BATH + "manager")


#define ARCADE	ARCH; CARY; CEIL; COLM; COLT; PED; MIST; MISTE; POOL; POOLE;

#define ARCH	add_item("arches", \
    "Curved stone supports bearing the weight of the domed ceiling.\n")
#define CARY	add_item(({"caryatid", "caryatids", "carvings"}), \
    "A representation of a woman bearing a water jug upon her head.\n");
#define CEIL	add_item("ceiling", \
    "It is obscured by steam.\n")
#define COLM	add_item("columns", \
    "Marble pillars carved in the shape of caryatids.\n")
#define COLT	add_cmd_item(({"column", "columns", "carvings", "marble"}), \
    "touch", "It is smooth and slightly warm under your fingertips.\n")
#define DOOR	add_item(({"door", "doors"}), \
    "These doors are made of a heavy dark wood with iron hinges.\n")
#define MIST	add_item(({"mist","steam"}), \
    "White and rather dense, it rises from the surface of the pool.\n")
#define MISTE	add_cmd_item(({"mist","steam"}), "enter", \
    "You have already done so.\n")
#define PED	add_item(({"pedestal", "pedestals"}), \
    "The flaring marble base of the columns.\n")
#define POOL	add_item(({"pool", "water"}), \
    "It looks warm and inviting.\n")
#define POOLE	add_cmd_item("pool" , "enter", \
    "You cannot do that from here.\n")

#endif  /* __BATH_H__ */
