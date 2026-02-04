
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define NORTH_EXIT   MANSION + "second/passage4.c"
#define SOUTH_EXIT   MANSION + "second/passage6.c"
#define CHAIR        MANSION + "second/chair.c"

#define OTHER           MANSION + "second/gallery_w"
#define PLAYER_I_STANDS "_player_i_stands"

init()
{
    ::init();
    add_action("hole", "look");
}

create_room()
{
    object ob;
    
    set_short("Dark Passage");
    set_long(BS(
    	"The passageway opens into a small room here.  There " +
        "are no signs of life, yet a small chair has been " +
        "placed against the eastern wall. The passageway " +
        "continues both to the north and south.\n"));
 
    add_exit(SOUTH_EXIT, "south", 0);
    add_exit(NORTH_EXIT, "north", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    
    add_item(({"floor", "boards", "floorboards"}),
        "The floor boards are buried deep below vast quantities of dust.\n");

    add_item(({"dust", "thick dust"}), "@@dusty_floor");

    add_cmd_item(({"dust", "thick dust"}), ({"clean", "wipe"}),
        "There is so much dust, you quickly give up hope.\n");

    add_item(({"footprint", "footprints"}), "@@footprint");

    add_item(({"passage", "tiny passage", "passages", "passageway"}),
        "The passageway is very dark and twisty.\n");

    add_item("wall",
        "There is a small hole that you can look through.\n");
    add_item("hole", "You'll have to look through it.\n");
        
    add_item("chair", "A small uncomfortable chair.\n");
    add_cmd_item("chair", ({"get", "take"}),
        "The chair seems to be attached to the floor!\n");
    
    ob = clone_object(CHAIR);
    ob->move(this_object());
}

dusty_floor()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50)) {
        return "The dust is very thick here.  You can just about make " +
               "out some footprints.\n";
        }
    return "The dust is very thick here.  You can feel your feet " +
           "sinking into the thickness.\n";
}

footprint()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50)) {
        return "There are some footprints around the chair.\n";
            }
    return "You recognise the footprints as your own.\n";
}

whoisit(object ob)
{
    if (TP->query_met(ob))
        return ob->query_name();
    return (LANG_ADDART(ob->query_nonmet_name()));
}
    
hole(string str)
{
    int     i, n, n2;
    mixed   room, *plist;
    string  race, ppl;

    if (!str)  return 0;
    if (sscanf(str, "through hole at %s", ppl)==1 ||
          sscanf(str, "through the hole at %s", ppl)==1 ||
          sscanf(str, "at %s through hole", ppl)==1 ||
          sscanf(str, "at %s through the hole", ppl)==1 )  {
        write("The hole is too small to look at specific things.\n");
        return 1;
    }
    if (str!="through hole" && str!="through the hole")  return 0;

    race = TP->query_race_name();
    if (!TP->query_wiz_level())
        if (((race=="dwarf") || (race=="gnome") ||
             (race=="hobbit")) && (!TP->query_prop(PLAYER_I_STANDS)))  {
           write("You are too short to reach the hole.\n");
           return 1;
           }
        else if (((race!="dwarf") && (race!="gnome") &&
                  (race!="hobbit")) &&
                  (TP->query_prop(PLAYER_I_STANDS)))  {
           write("Standing on the chair makes you " +
                 "too tall to look through the hole!\n");
           return 1;
           }
        
    say(QCTNAME(TP) + " puts " +
            TP->query_possessive() + " face to the wall.\n");
        
    if (!(room = find_object(OTHER)))   {
        write("You look into a long hallway full of portraits of " +
              "numerous people.\n");
        return 1;
    }
    
    if (((room->query(OBJ_I_LIGHT)) >
            -(TP->query_prop(LIVE_I_SEE_DARK))))   {
        write("It's too dark for you to see anything!\n");
        tell_room(room, "You feel as though someone is " +
                        "trying to look for you!\n");
        return 1;
    }

    switch ((random(8))+1)  {
        case 1:
            tell_room(room, "You feel as if the eyes on the portrait " +
                            "are following you around the room!\n");
            break;
        case 2:
            tell_room(room, "You feel as if someone is watching you!\n");
            break;
        case 3:
            tell_room(room, "An eerie feeling passes over you!\n");
            break;
        case 4: tell_room(room,
            "You think you see movement from the portrait!\n");
            break;
        case 5: tell_room(room,
            "You suddenly feel as though you have a sixth sense!\n");
            break;
        case 6: tell_room(room, "You catch a glimpse of the eyes " +
            "on the portrait roving about the room!!\n");
            break;
        default:
            tell_room(room, "You feel as though someone is watching you!\n");
            break;
    }

    plist = all_inventory(room);

/* Someone has destructed the Large painting of the Marquis!!!  */
    if (!sizeof(plist))  {
        write("The hole has been filled in by someone!\n");
        return 1;
    }

    n=0;  n2=0;  ppl = "";
    for (i=0; i < sizeof(plist); i++ )
        if (living(plist[i]))
            n++;

    if (!n)  {
        write("You look into a long hallway full of portraits of " +
              "numerous people.\n");
        if (sizeof(plist)!=1)
            write("You notice some objects lying around.\n");
        return 1;
    }
    
    for (i=0; i < sizeof(plist); i++ )
        if (living(plist[i]))
            if (CAN_SEE(TP, plist[i]))
                if (n==1)  {
                    write("You can see " + whoisit(plist[i]) +
                          " looking at some paintings.\n");
                    return 1;
                }
                else {
                    n2++;
                    if (n2==n)
                    	ppl = ppl + " and ";
                    if ((n2!=1) && (n2!=n))
                        ppl = ppl + ", ";
                    ppl = ppl + whoisit(plist[i]);
                }
    write(BS("You look into a long hallway of portraits where " +
             ppl + " are looking at the paintings.\n"));
    return 1;
}


