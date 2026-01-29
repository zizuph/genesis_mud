/* The mephisto room. ~solace/puzzle/locations/mephisto */

#include "../defs.h"
#include "/sys/macros.h"

inherit ROOM_DEFS;

#define FAINT_RING ({ "start.c", "entrance.c", "apollyon.c", "tuttivillus.c" })

#define FAINT ({ "You hear a faint ringing sound.",                          \
                 "The sound of bells reaches your ears.",                    \
                 "A faint chiming sound comes from nearby.",                 \
                 "You notice an almost imperceptible ringing noise."         })

#define LOUD  ({ "You hear a loud GONG GONG GONG sound nearby.",             \
                 "A loud ringing sound reverberates about the room!",        \
                 "You hear the sound of a chiming bell coming from nearby.", \
                 "The almost deafening sound of bells nearby startles you."  })

int ringbell_alarm, killmouse_alarm, mouse_alarm;

void start_mouse()
{
    if(!pointerp(get_alarm(mouse_alarm)))
        mouse_alarm = set_alarm(itof(30 + random(61)), 0.0, "produce_mouse");
}

void reset_puzzle_room()
{
    object lever;

    seteuid(getuid(TO));
    lever = clone_object(OBJECTS + "lever");

    lever->set_lever_number(1);
    lever->move(TO);

    start_mouse();
}

void create_puzzle_room()
{
    set_short("The Mephisto room");
    set_long("You are suprised by the opulence of this room. Every part of "+
        "it is a different shade of red. The walls are covered by red drapes "+
        "and the floor by a lush sunset-coloured deep-pile rug. A soft glow "+
        "emanates from many small dancing lights circling the room above "+
        "your head. In one corner, you see a bell-pull and almost immediately "+
        "below this, a small round mouse-hole. There is also an arched "+
        "doorway leading southeastwards to another room.\n");

    add_exit(LOCATIONS + "azazel", "southeast", 0, 1);

    add_item("floor", "It seems to be covered by a rug.\n");

    add_item(({"doorway", "arched doorway"}), "An exit from this room to "+
        "the room southeast of here. You see nothing more of interest.\n");

    add_item(({"drapes", "red drapes"}), "The drapes are a deep mauve and "+
        "hang the full length of the walls. They seem to serve no other "+
        "purpose than to make the room more cosy and homely.\n");

    add_item(({"wall", "walls"}), "The walls can barely be seen behind the "+
        "drapes that cover them. The only thing of interest is the mouse-"+
        "hole beneath a bell-pull in one corner. It spoils the beauty of "+
        "room.\n");

    add_item(({"hole", "mouse-hole", "small mouse-hole", "round mouse-hole",
        "small round mouse-hole"}), "The mouse-hole seems to have been "+
        "gnawed into the wall just below the foot of the drapes, beside a "+
        "bell-pull. You can't see inside it; it's far too dark in there.\n");

    add_item(({"rug", "lush rug", "deep-pile rug", "lush deep-pile rug", 
        "sunset-coloured rug", "lush sunset-coloured rug", "sunset-coloured "+
        "deep-pile rug", "lush sunset-coloured deep-pile rug"}), "The rug "+
        "looks very soft and feels warm underfoot. You see nothing more of "+
        "interest about it.\n");

    add_item(({"bell", "bell-pull"}), "The bell-pull seems to be made of "+
        "the same material as the drapes with the exception that it is "+
        "connected to a rope that disappears into a small hole in the "+
        "ceiling. You notice that part of it looks as if it has been "+
        "gnawed by a pair of small teeth.\n");

    add_item(({"lights", "small lights", "dancing lights", "small dancing "+
        "lights"}), "The lights are quite bizarre! You have no idea what "+
        "they are. They seem to be tiny pin-points of light floating round "+
        "and round the room in mid-air. They glow with a soft ethereal light "+
        "and although they seem to have a mind of their own, it is clear "+
        "that their purpose is to light the room.\n");

    reset_puzzle_room();
}

void init()
{
    ::init();

    add_action("pull_rope", "pull");
}

int pull_rope(string str)
{
    if(!strlen(str))
        return 0;

    if(str == "rope" || str == "bell" || str == "bell-pull")
    {
        TP->catch_msg("You grasp the bell-pull and give it a good yank.\n");

        tell_room(E(TP), QCTNAME(TP)+" graps the bell-pull and gives it a "+
            "good yank.\n", TP);

        if(!pointerp(get_alarm(ringbell_alarm)))
            ringbell_alarm = set_alarm(1.0, 0.0, "ring_bell");
    }
    else
        return 0;

    return 1;
}

void ring_bell()
{
    int i;
    object obj;
    string *rooms = get_dir(LOCATIONS + "*.c");

    for(i = 0; i < sizeof(rooms); i++)
    {
        obj = find_object(LOCATIONS + rooms[i]);

        if(member_array(rooms[i], FAINT_RING) == -1)
            tell_room(obj, LOUD[random(sizeof(LOUD))] + "\n");
        else
            tell_room(obj, FAINT[random(sizeof(FAINT))] + "\n");
    }
}

void produce_mouse()
{
    object mouse;

    seteuid(getuid(TO));
    mouse = clone_object(CREATURES + "mouse");

    tell_room(TO, "Out of the corner of your eye, you notice a "+QSHORT(mouse)+
        " scamper out of the mouse-hole.\n", mouse);

    mouse->move(TO);
}

void enter_inv(object obj, object from)
{
    object mouse;

    if(MASTER_OB(obj) == OBJECTS + "mouse_trap")
    {
        if(obj->query_ready())
        {
            mouse = present("mouse", TO);

            if(objectp(mouse))
                if(!pointerp(get_alarm(killmouse_alarm)))
                    killmouse_alarm = set_alarm(1.0, 0.0, "kill_mouse");
        }
    }

    ::enter_inv(obj, from);
}

void kill_mouse()
{
    object mouse, trap;

    trap = present("trap", TO);
    mouse = present("mouse", TO);

    if(objectp(mouse) && objectp(trap))
        mouse->kill_me(trap);
}
