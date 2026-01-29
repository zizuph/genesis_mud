/*
 *  IGARD_WALL + "gate_test.c"
 *
 *  Great southern gate of Isengard.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs_new.c";

public void        create_gondor();
public string      exa_inscription();
public int         declare_myself(string str);
public int         knock_gate(string str);
public int         arrow_attack();
public int         permit_entry();
public string      long_desc();
public int         check_huorn();

object             actor;

string *plainrooms = ({IGARD_PLAIN + "east_road1.c",
IGARD_PLAIN + "east_road3.c",
IGARD_PLAIN + "east_road5.c",
IGARD_PLAIN + "east_road7.c",
IGARD_PLAIN + "east_road9.c",
IGARD_PLAIN + "south_road1.c",
IGARD_PLAIN + "south_road3.c",
IGARD_PLAIN + "south_road5.c",
IGARD_PLAIN + "south_road7.c",
IGARD_PLAIN + "south_road9.c",
IGARD_PLAIN + "west_road1.c",
IGARD_PLAIN + "west_road3.c",
IGARD_PLAIN + "west_road5.c",
IGARD_PLAIN + "west_road7.c",
IGARD_PLAIN + "west_road9.c",
IGARD_PLAIN + "north_road1.c",
IGARD_PLAIN + "north_road3.c",
IGARD_PLAIN + "north_road5.c",
IGARD_PLAIN + "north_road7.c",
IGARD_PLAIN + "north_road9.c",
IGARD_PLAIN + "northeast_road1.c",
IGARD_PLAIN + "northeast_road3.c",
IGARD_PLAIN + "northeast_road5.c",
IGARD_PLAIN + "northwest_road1.c",
IGARD_PLAIN + "northwest_road3.c",
IGARD_PLAIN + "northwest_road5.c",
IGARD_PLAIN + "southeast_road1.c",
IGARD_PLAIN + "southeast_road3.c",
IGARD_PLAIN + "southeast_road5.c",
IGARD_PLAIN + "southwest_road1.c",
IGARD_PLAIN + "southwest_road3.c",
IGARD_PLAIN + "southwest_road5.c"});

string *pathrooms = ({IGARD_PLAIN_PATHS + "ne_path1a.c",
IGARD_PLAIN_PATHS + "ne_path1c.c",
IGARD_PLAIN_PATHS + "ne_path2a.c",
IGARD_PLAIN_PATHS + "ne_path2c.c",
IGARD_PLAIN_PATHS + "sw_path1a.c",
IGARD_PLAIN_PATHS + "sw_path1c.c",
IGARD_PLAIN_PATHS + "sw_path2a.c",
IGARD_PLAIN_PATHS + "sw_path2c.c",
IGARD_PLAIN_PATHS + "nw_path1a.c",
IGARD_PLAIN_PATHS + "nw_path1c.c",
IGARD_PLAIN_PATHS + "nw_path2a.c",
IGARD_PLAIN_PATHS + "nw_path2c.c",
IGARD_PLAIN_PATHS + "se_path1a.c",
IGARD_PLAIN_PATHS + "se_path1c.c",
IGARD_PLAIN_PATHS + "se_path2a.c",
IGARD_PLAIN_PATHS + "se_path2c.c"});


#define PLAIN_AREA_IDENT            94235643
#define PLAIN_AREA_RANGE            32
#define PLAIN_PATH_IDENT            95346754
#define PLAIN_PATH_RANGE            16
#define ENTRY_LOG        (IGARD_LOG + "igardentry")


public void
create_gondor()
{
    set_short("The great southern gate of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();

    add_item(({"inscription", "weathered inscription"}), &exa_inscription());
    add_cmd_item(({"inscription", "weathered inscription"}), "read",
        &exa_inscription());

    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_item(({"door", "doors", "gate", "gates", "entrance",
        "great gate", "great southern gate"}), "Two mighty doors of "
        + "iron tower above you. Each door stands more than thirty "
        + "feet high and together they span almost twenty across. The "
        + "iron is very weathered and scratched, but no dent can be "
        + "seen on the face of these doors for they have never been "
        + "broken. The doors are mounted on large iron hinges.\n");
    add_item(({"iron", "scratches", "scratch"}), "The doors are made "
        + "of iron quarried from mines in the Misty Mountains. The "
        + "iron is weathered and scratched, but no dent can be seen "
        + "anywhere.\n");
    add_item(({"hinge", "hinges", "iron hinge", "iron hinges",
        "large hinge", "large hinges"}), "The doors are mounted on "
        + "several large iron hinges bolted into the rock of the "
        + "ring wall. Through a marvel of engineering, the massive "
        + "doors are balanced on the hinges in such a way that a single "
        + "person can open or close them with a push.\n");
    add_item(({"arch", "archway", "stone arch"}), "A great arch of "
        + "stone encloses the mighty iron doors. Made from the same "
        + "daunting black stone as the ring wall, the arch bears a "
        + "weathered inscription at the top.\n");
    add_item(({"wall", "ring wall", "ringed wall"}), "A great wall "
        + "of black stone stands at least one hundred feet tall and "
        + "curves away to the west and east. It appears to be made "
        + "partly from the natural landscape but also by the hand of "
        + "Men. Standing this close to the wall makes it impossible "
        + "to determine how far it extends or what lies on the other "
        + "side. You can, however, see the peaks of the Misty "
        + "Mountains above it.\n");
    add_item(({"landscape", "natural landscape", "terrain"}), "Here at "
        + "the foot of the Misty Mountains, the landscape is partly flat "
        + "but also has many sudden projections of black rock. The wall "
        + "before you is made from a combination of these natural "
        + "outcroppings as well as quarried stone worked by the hands "
        + "of Men.\n");
    add_item(({"rock", "black rock"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"street", "wide street"}), "A wide street leads south "
        + "from the great gate. It is made from great flat stones, "
        + "squared and laid with great skill. No blade of grass can "
        + "be seen in any joint.\n");
    add_item(({"stones", "flat stones", "great flat stones"}), "The "
        + "flat and squared stones are made from the same black rock "
        + "used in the construction of the ring wall.\n");
    add_item(({"isengard", "fortification"}), "The fortification of "
        + "Isengard stands "
        + "directly north from here. It can only be entered through "
        + "this gate in the southern section of its ring wall.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_EXTERIOR + "west_1.c",      "west");
    add_exit(IGARD_EXTERIOR + "east_1.c",      "east");
    add_exit(IGARD_EXTERIOR + "status_room.c", "south", check_huorn, 2, 0);

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


string
long_desc()
{
    return "Two mighty doors of iron rise above you here at the "
      + "great southern gate of Isengard. The doors are set beneath an "
      + "arch in the great ringed wall of black sheer rock that reaches "
      + "toward the sky like a towering cliff." + sky_desc() 
      + " The vast immensity of this place, a natural wonder yet hewn by "
      + "the hands of men, humbles even the proudest soul to knock at her "
      + "gates. There is a weathered inscription carved into the black stone "
      + "of the arch. For those unwelcome at Isengard, a street leads south "
      + "and away from the shadow of the massive ring wall.\n";
}


public string
exa_inscription()
{
    return "The inscription reads:\n"
+" ___________________________________________________________\n"
+"|o_________________________________________________________o|\n"
+"||                                                         ||\n"
+"||        Stranger, <declare> thyself a friend             ||\n"
+"||        and enter freely by pushing upon the doors.      ||\n"
+"||                                                         ||\n"
+"||        All others should flee lest the wrath of         ||\n"
+"||        Lord Saruman be awakened.                        ||\n"
+"||_________________________________________________________||\n"
+"|o_________________________________________________________o|\n";

}


int
arrow_attack()
{
    int healed, health, pain, ouch;

    healed = TP->query_max_hp();
    health = TP->query_hp();
    pain = (healed/2);
    ouch = (health/2);
    actor = TP;

    write("A cloud of arrows erupts from the wall above you. Many of "
        + "them skitter off the stones of the street, but several of "
        + "them find their mark. Ouch!\n");
    tell_room(environment(actor), "A cloud of arrows erupts from the "
        + "wall overhead. Many of them skitter off the stones of the "
        + "street, but several of them strike " + QTNAME(TP) + ".\n", 
        ({actor}));

    if (health <= pain)
    {
        TP->set_hp(ouch);
        return 1;
    }

    else
    {
    TP->set_hp(pain);
    }

    return 1;
}


int
permit_entry()
{
    string pname;
    int plain_loc, path_loc;

    actor = TP;
    pname = TP->query_real_name();
    plain_loc = NAME_TO_RANDOM(pname, PLAIN_AREA_IDENT, PLAIN_AREA_RANGE);
    path_loc  = NAME_TO_RANDOM(pname, PLAIN_PATH_IDENT, PLAIN_PATH_RANGE);

    write("You push on the massive iron doors with both hands. Much to "
        + "your surprise, they swing easily upon their hinges. You "
        + "quickly slip inside as the doors close behind you.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " pushes on the massive "
        + "iron doors with both hands. The doors open effortlessly and "
        +  PRONOUN(actor) + " slips quietly inside.\n"
        + "The doors return to their original position.\n", 
        ({actor}));
    tell_room(IGARD_WALL + "gate_tun1", QCPNAME(TP) + " footsteps "
        + "echo across the tunnel as " + PRONOUN(actor) + " enters "
        + "through the massive iron doors.\n"
        + "The doors return to their original position.\n");

    TP->move_living("M", IGARD_WALL + "gate_tun1", 1, 0);

    write_file(ENTRY_LOG, "South gate was entered by " + 
	       TP->query_name() + " (" + 
	       TP->query_average_stat() + ") on " + ctime(time()) +
	       ".\n");  

    if (BADDIE)
    {
    return 1;
    }

    switch (random(3))
    {
    case 0:
    case 1:
        break;
    case 2:
        if(file_size(plainrooms[plain_loc]) != -1)
        {
        plainrooms[plain_loc]->teleledningsanka();
          if(!present("_ambush_object_", find_object(plainrooms[plain_loc])))
            {
          clone_object(IGARD_OBJ + "ambush_object.c")->move(plainrooms[plain_loc]);
            }
        }

        if(file_size(pathrooms[path_loc]) != -1)
        {
        pathrooms[path_loc]->teleledningsanka();
          if(!present("_ambush_object_", find_object(pathrooms[path_loc])))
          {
          clone_object(IGARD_OBJ + "ambush_object.c")->move(pathrooms[path_loc]);
          }
        }
        break;
    default:
        break;
    }

    return 1;
}


public int
knock_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What is it that you are trying to knock on?\n");
       return 0;
    }

    write("A voice from above shouts down at you: Read the inscription, "
        + "you fool! Do you think we have all day to be answering the "
        + "door?\n");
    tell_room(environment(actor), "A voice from above shouts at " 
        + QTNAME(actor) + ": Read the inscription, you fool! Do you "
        + "think we have all day to be answering the door?\n", ({actor}));
    return 1;

}


public int
push_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What would you like to push on?\n");
       return 0;
    }

    write("A voice from above shouts down at you: Read the inscription, "
        + "you fool!\n");
    tell_room(environment(actor), "A voice from above shouts at " 
        + QTNAME(actor) + ": Read the inscription, you fool!\n", ({actor}));
    return 1;

}


public int
open_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What are you trying to open?\n");
       return 0;
    }

    write("A voice from above shouts down at you: Read the inscription, "
        + "you fool!\n");
    tell_room(environment(actor), "A voice from above shouts at " 
        + QTNAME(actor) + ": Read the inscription, you fool!\n", ({actor}));
    return 1;

}

public int
declare_myself(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "friend" && str != "myself friend"
                                         && str != "myself a friend"))
    {
	      NF0("Are you trying to declare yourself a friend?\n");
       return 0;
    }

    if (TP->query_leading_steed() || TP->query_steed())
    {
        write("A voice from above shouts down at you: Leave your steed "
            + "outside, fool! The Boss does not want its dung in here!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Leave your steed outside, fool! The Boss "
            + "does not want its dung in here!\n", 
            ({actor}));
        return 1;
    }


    if (GOODIE)
    {
        if (ENEMY)
        {
        write("A voice from above shouts down at you: Enemy of Isengard, "
            + "flee whilst you can!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Enemy of Isengard, flee whilst you can!\n", 
            ({actor}));
        arrow_attack();
        return 1;
        }

        if (FRIEND)
        {
        write("A voice from above shouts down at you: Hmm, there is "
            + "something about you that does not add up, stranger. "
            + "You may pass, but we shall be keeping a close eye on "
            + "you. Start no trouble!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Hmm, there is something about you that "
            + "does not add up, stranger. You may pass, but we shall "
            + "be keeping a close eye on you. Start no trouble!\n", 
            ({actor}));
        permit_entry();
        return 1;
        }

        else
        {
        write("A voice from above shouts down at you: You have no "
            + "business in Isengard, stranger. Begone!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": You have no business in Isengard, "
            + "stranger. Begone!\n", 
            ({actor}));
        return 1;
        }

    }

    if (BADDIE)
    {
        if (ENEMY)
        {
        write("A voice from above shouts down at you: Traitor of Isengard, "
            + "you are no longer welcome here! Begone!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Traitor of Isengard, you are no longer "
            + "welcome here! Begone!\n", ({actor}));
        arrow_attack();
        return 1;
        }

        else
        {
        write("A voice from above shouts down at you: Welcome, friend "
            + "of Isengard! You may pass.\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Welcome, friend of Isengard! You may "
            + "pass.\n", ({actor}));
        permit_entry();
        return 1;
        }
    }

    else
    {
    NF0("There seems to be something wrong with the gate: please "
        + "make a bug report.\n");
    }

}


public void
init() 
{
    ::init();

    add_action(declare_myself,  "declare");
    add_action(knock_gate,      "knock");
    add_action(push_gate,       "push");
    add_action(open_gate,       "open");
}


public int
check_huorn()
{

    if (TP->query_npc())
    {
        return 1;
	   }


	    write("You turn your back on the the great southern gate of "
        + "Isengard and leave its brooding menace behind.\n");
	       return 0;
}








