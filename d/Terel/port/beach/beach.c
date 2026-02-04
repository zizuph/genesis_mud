inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define MON       "/d/Terel/port/monster/"
#define BEA       "/d/Terel/port/beach/"

#define NEXT_TO_FENCE 0
#define NEXT_TO_BWOOD 1
#define NEXT_TO_CLIFF 2
#define NEXT_TO_WATER 3

#define FENCE     ({BEA+"b1",  BEA+"b6",  BEA+"b7",  BEA+"b13"})
#define BWOOD     ({BEA+"b20", BEA+"b21", BEA+"b22"})
#define CLIFF     ({BEA+"b5",  BEA+"b11", BEA+"b12", BEA+"b19"})
#define WATER     ({BEA+"b13", BEA+"b14", BEA+"b15", BEA+"b16", BEA+"b17", \
                    BEA+"b18", BEA+"b19"})

#define REMAINS   ({"star-fish", "clam", "haddock", "sea-snail", "seaweed"})
#define MONSTERS  ({MON+"crab", MON+"clam", MON+"gull"})
#define TREASURE  ({BEA+"shoe", BEA+"bottle", BEA+"knife", BEA+"hat", \
                    BEA+"wood", BEA+"glove"})
#define SMELLS    ({"rotten fish", "salt water", "moulded seaweed", \
                    "your own odour"})
#define MAX_LEVEL  5
#define FAT_LIM    5

public void    create_beach();
public string *query_monster();
public int     add_monster(string m);
public string *query_treasures();
public int    *query_levels();
public int     add_treasure(string s, int level);
public void    init_beach();
public void    reset_beach();
public void    find_treasure();
public int     next_to_fence(mixed room);
public int     next_to_water(mixed room);
public int     next_to_bwood(mixed room);
public int     next_to_cliff(mixed room);
public int     next_to_what(mixed room, int type);
public int     add_entrance(string s, string desc, int level);
public string *query_entrances();
public int     check_entrance(string s);
public int     open_entrance(string s);

static object *monster;
static string *mon, *tre, *ent, *edesc;
static int *lev, *elev;
static int dig_level = 0;
static int wind_id = 0;
static int wet = 0;

public void
reset_room()
{
    int i, level;
    object ob;

    for (i=0; i<sizeof(mon); i++) {
        if (sizeof(monster) == 0 || i >= sizeof(monster)) {
           ob = clone_object(mon[i]);
           if (sizeof(monster) == 0)
               monster = ({ ob });
           else
               monster += ({ ob });
           ob->move_living(0, this_object());
        } else if (!monster[i]) {
           ob = clone_object(mon[i]);
           monster[i] = ob;
           ob->move_living(0, this_object());
        }
    }

    tre = ({ }); lev = ({ });

    for (i=0; i<sizeof(TREASURE); i++) {
        if (random(3) == 0) {
            level = random(MAX_LEVEL) + 1;
            add_treasure(TREASURE[i], level);
        }
    }

    reset_beach();
}

public void
create_room()
{
    int i;

    set_short("On the beach");
    set_long("Despite the cold weather this sandy beach is quite " +
             "nice. The sand is fine and feels very smooth. " +
             "Here and there in the sand you see shells and " +
             "the scattered remains of some dead sea animals. " +
             "North of the beach there are thick brushwood. " +
             "East of the beach there are high cliffs and south " +
             "is the vast sea. West of the beach there is a " +
             "high wooden fence. There is a distinct smell " +
             "in the air." +
             VBFC("my_hole_long") + "\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item(({"fence", "wooden fence"}), VBFC("my_fence"));
    add_item(({"cliff", "cliffs"}), VBFC("my_cliff"));
    add_item(({"brushwood"}), VBFC("my_bwood"));
    add_item(({"sea", "water"}), VBFC("my_water"));
    add_item(({"sand"}), "It is very smooth. It feels a bit warm too, at " +
                         "least compared to the icy wind." +
                         VBFC("my_sand") + "\n");
    add_item(({"shell",  "shells"}), "The shells look old and polished by" +
                                     " the sand.\n");
    add_item(({"remains", "animal"}), VBFC("my_remains"));
    add_item(({"hole"}), VBFC("my_hole"));

    mon = ({ });

    for (i=0; i<sizeof(MONSTERS); i++) {
        if (random(3) == 0) {
            add_monster(MONSTERS[i]);
        }
    }

    create_beach();

    reset_room();
}

public string
my_fence()
{
    if (next_to_fence(0)) {
        return "The fence surrounding the village is made of wood and it " +
               "is about 3 meters high. It's impossible to climb.\n";
    } else {
        return "It surrounds the village. You have to go further west to " +
               "examine it more closely.\n";
    }
}

public string
my_cliff()
{
    if (next_to_cliff(0)) {
        return "The cliffs seem to be made of limestone and they are at " +
               "least 100 meters high. You can't find a way to climb " +
               "the wall.\n";
    } else {
        return "The cliffs to the east are high. You must go closer to see " +
               "what kind of stone it is.\n";
    }
}

public string
my_bwood()
{
    if (next_to_bwood(0)) {
        return "It is very thick. There is no way you can go in there.\n";
    } else {
        return "The brushwood is just north of the beach.\n";
    }
}

public string
my_water()
{
    if (next_to_water(0)) {
        return "It feels very cold. You suspect you wouldn't survive many " +
               "minutes swimming in it. To the west you see some kind of " +
               "wreck stranded on some rocks.\n";
    } else {
        return "You have to go further south to examine it more closely. " +
               "It looks empty though apart from a few seagulls circling " +
               "for food.\n";
    }
}

public string
my_remains()
{
    string str;

    str = REMAINS[random(sizeof(REMAINS))];

    return "This piece looks like a dead " + str + ".\n";
}

public string
my_sand()
{
    string str;

    if (wet) {
        return " It is wet.";
    } else {
        return " The surface is dry, but the sand is wet underneath.";
    }
}

public void
create_beach()
{
}

public int
add_monster(string m)
{
    if (file_size(m + ".c") > 0) {
        if (sizeof(mon) == 0)
            mon = ({ m });
        else
            mon += ({ m });
        return 1;
    }
    return 0;
}

public string *
query_monster()
{
    return mon;
}

public int
add_treasure(string s, int level)
{
    if (file_size(s + ".c") > 0 && level > 0) {
        if (sizeof(tre) == 0) {
            tre = ({ s });
            lev = ({ level });
        } else {
            tre += ({ s });
            lev += ({ level });
        }
        return 1;
    }
    return 0;
}

public string *
query_treasures()
{
    return tre;
}

public int
add_entrance(string s, string desc, int level)
{
    if (file_size(s + ".c") > 0 && level > 0) {
        if (sizeof(ent) == 0) {
            ent   = ({ s });
            edesc = ({ desc });
            elev  = ({ level });
        } else {
            ent   += ({ s });
            edesc += ({ desc });
            elev  += ({ level });
        }
        return 1;
    }
    return 0;
}

public string *
query_entrances()
{
    return ent;
}

public int *
query_levels()
{
    return lev;
}

public void
init()
{
    ::init();

    add_action("do_dig",   "dig");
    add_action("do_smell", "smell");
    add_action("do_enter", "enter");
    if (next_to_water(0)) {
        add_action("do_swim", "swim");
        add_action("do_swim", "dive");
    }
    if (next_to_cliff(0) || next_to_fence(0)) {
        add_action("do_climb", "climb");
    }
    init_beach();
}

public void
init_beach()
{
}

public void
reset_beach()
{
}

public int
do_swim(string str)
{
    notify_fail("Swim in what?\n");
    if (!str) return 0;
    if (str != "in water" && str != "in sea" &&
        str != "water"    && str != "sea") return 0;

    write("When you feel the water temperature you realize it is far " +
          "too cold for a swim.\n");
    say(QCTNAME(this_player()) + " was about to take a swim in the sea, but " +
        "had second thoughts when " + this_player()->query_pronoun() +
        " felt the water temperature.\n");
    return 1;
}

public int
do_climb(string str)
{
    notify_fail("Climb what?\n");
    if (!str) return 0;

    if (str != "fence" && str != "cliff") return 0;

    if (str == "cliff" && !next_to_cliff(0)) return 0;
    if (str == "fence" && !next_to_fence(0)) return 0;

    write("The " + str + " is impossible to climb.\n");
    if (str == "fence")
        say(QCTNAME(this_player()) + " tries to climb the fence.\n");
    else if (str == "cliff")
        say(QCTNAME(this_player()) + " tries to climb the cliff.\n");

    return 1;
}

public int
do_dig(string str)
{
    object shovel;

    notify_fail("Dig with what?\n");
    if (!str) return 0;

    if (str == "with hands" || str == "with hand") {
        shovel = 0;
    } else if (str == "with shovel") {
        shovel = present("shovel", this_player());
        notify_fail("You don't have that!\n");
        if (!shovel) return 0;
    } else {
        return 0;
    }

    if (this_player()->query_fatigue() <= FAT_LIM) {
        write("You are too tired to dig.\n");
        say(QCTNAME(this_player()) + " tries to dig but is too tired.\n");
        return 1;
    }

    if (shovel) {
        if (dig_level < MAX_LEVEL) {
            if (dig_level == 0) {
               write("You start to dig a hole in the sand using your " +
                     shovel->short() + ".\n");
            } else {
               write("You dig a deeper hole in the sand using your " +
                     shovel->short() + ".\n");
            }
            say(QCTNAME(this_player()) + " digs a hole in the sand " +
                "using the " + shovel->short() + ".\n");
            dig_level++;
            find_treasure();
            this_player()->add_fatigue(-FAT_LIM);
        } else {
            write("It's impossible to dig further here.\n");
        }
    } else {
        if (dig_level == 0) {
            write("You dig a small hole in the sand with your bare hands.\n");
            say(QCTNAME(this_player()) + " digs a small hole in the sand " +
                "with " + this_player()->query_possessive() + " hands.\n");
            dig_level = 1;
            find_treasure();
            this_player()->add_fatigue(-FAT_LIM);
        } else {
            write("It's impossible to dig further with your bare hands.\n");
            say(QCTNAME(this_player()) + " doesn't succeed to dig a deeper " +
                "hole in the sand with " + this_player()->query_possessive() +
                " bare hands.\n");
        }
    }

    return 1;
}

public void
do_blow()
{
    if (random(2)) {
        tell_room(this_object(), "A sudden gust of wind makes the sand " +
                  "whirl and twirl.\n");
        if (dig_level) {
            tell_room(this_object(), "Some sand blows into the hole.\n");
            dig_level--;
        }
        wet = 0;
    } else {
        tell_room(this_object(), "A small wave of water suddenly rolls in " +
                  "from the sea.\n");
        if (dig_level) {
            tell_room(this_object(), "Some sand gets into the hole.\n");
            dig_level--;
        }
        wet = 1;
    }
    
    if (dig_level || !wind_id)
        return;
        
    if (sizeof(filter(all_inventory(this_object()), interactive)))
        return;
        
    remove_alarm(wind_id);
    wind_id = 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || !interactive(ob) || wind_id)
        return;

    wind_id = set_alarm(itof(60 + random(30)),
                        itof(60 + random(60)), do_blow);
}

public string
my_hole_long()
{
    if (dig_level == 0) {
        return "";
    } else if (dig_level == 1) {
        return " There is a small hole in the sand here.";
    } else if (dig_level == 2) {
        return " There is a hole in the sand here.";
    } else if (dig_level >= 3) {
        return " There is a deep hole in the sand here.";
    }
}

public string
my_hole()
{
    int i, depth;
    string s="";

    depth = 20*dig_level;

    if (dig_level == 0) {
        return "There is no hole here.\n";
    } else if (dig_level >= 1) {
        for (i=0; i<sizeof(ent); i++) {
            if (elev[i] <= dig_level) s += edesc[i];
        }
        if (!strlen(s)) s = "\n";
        return "The hole is roughly "+depth+" centimeters deep. " + s;
    }
}

public void
find_treasure()
{
    int i;
    object ob;

    for (i=0; i<sizeof(tre); i++) {
        if (lev[i] == dig_level && strlen(tre[i])) {
            seteuid(getuid());
            ob = clone_object(tre[i]);
            write("You dug up something.\n");
            ob->move(this_object(), 1);
            tre[i] = "";
        }
    }
    for (i=0; i<sizeof(ent); i++) {
        if (elev[i] <= dig_level) {
            write(edesc[i]);
            write("You can probably reach it by entering the hole.\n");
        }
    }
}

public int
to_sea()
{
    string race, room;

    race = this_player()->query_race_name();

    if (race == "seagull" || race == "crab" || race == "clam") {
        room = WATER[random(sizeof(WATER))];
        if (room == file_name(this_object())) return 1;
        this_player()->move_living("leaves south", room);
        return 1;
    }
    write("The sea is far too cold for a swim.\n");
    return 1;
}

public int
do_smell()
{
    string what;

    what = SMELLS[random(sizeof(SMELLS))];

    write("You inhale deeply through your nose, and recognize " +
          "the smell of " + what + ".\n");
    say(QCTNAME(this_player()) + " inhales deeply through " +
        this_player()->query_possessive() + " nose.\n");

    return 1;
}

public int
do_enter(string str)
{
    int i;
    
    if (dig_level == 0) return 0;
    
    notify_fail("Enter what?\n");
    if (str != "hole") return 0;
    
    notify_fail("You are too big for entering the hole.\n");
    if (sizeof(ent) == 0) return 0;
    
    for (i=0; i<sizeof(ent); i++) {
        if (elev[i] <= dig_level) {
            write("You enter the hole.\n");
            this_player()->move_living("enters the hole", ent[i], 1);
            return 1;
        }
    }
    return 0;
}

public int
check_entrance(string s)
{
    int i;
    
    for (i=0; i<sizeof(ent); i++) {
        if (s == ent[i] && elev[i] <= dig_level) return 1;
    }
    return 0;
}

public int
open_entrance(string s)
{
    int i;
    
    for (i=0; i<sizeof(ent); i++) {
        if (s == ent[i] && elev[i] > dig_level) {
            dig_level = elev[i];
            return 1;
        }
    }
    return 0;
}

public int
next_to_water(mixed room)
{
    return next_to_what(room, NEXT_TO_WATER);
}

public int
next_to_fence(mixed room)
{
    return next_to_what(room, NEXT_TO_FENCE);
}

public int
next_to_cliff(mixed room)
{
    return next_to_what(room, NEXT_TO_CLIFF);
}

public int
next_to_bwood(mixed room)
{
    return next_to_what(room, NEXT_TO_BWOOD);
}

public int
next_to_what(mixed room, int type)
{
    int i;
    string *arr;

    if (type == NEXT_TO_FENCE)
        arr = FENCE;
    else if (type == NEXT_TO_WATER)
        arr = WATER;
    else if (type == NEXT_TO_CLIFF)
        arr = CLIFF;
    else if (type == NEXT_TO_BWOOD)
        arr = BWOOD;
    else
        return 0;

    if (!room) room = this_object();

    if (objectp(room)) {
       for (i=0; i<sizeof(arr); i++)
           if (file_name(room) == arr[i]) return 1;
    } else if (stringp(room)) {
       for (i=0; i<sizeof(arr); i++)
           if (room == arr[i] || room + ".c" == arr[i]) return 1;
    }

    return 0;
}
