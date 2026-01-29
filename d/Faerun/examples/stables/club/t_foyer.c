// Palmer, January 2003
// Evolved from:
// Old Fogey's club, borrowing from Vladimir and Dunstable's
// Smart Goblin club, Dunstable 12/94.


inherit "/lib/guild_support";
inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "/d/Shire/bits.h"

/* Prototypes */
int do_join(string str);
int do_abandon(string str);
int do_crop(string str);
int check_member();

#define RACE this_player()->query_race_name()
#define EQUESTRIAN_LOG "/d/Shire/log/equestrians"
#define STABLE_DIR "/d/Shire/bree/rooms/town/stable"
#define EQUESTRIAN_SOUL "/d/Shire/bree/rooms/town/stable/club/t_equestrian_soul"

string title;

void
create_room()
{
    set_short("Foyer of the Equestrian Society");
    set_long("A small room that serves as the foyer to the Equestrian " +
         "Society's Lounge. Paintings of horses and equestrians hang on " +
         "the walls. This is where horse lovers become members of the " +
         "Equestrian Society of Bree. A sign is fixed to one of the walls.\n");

    add_item(({"painting", "paintings"}),
        "Various paintings of horses and their riders hang from the walls.\n");

    add_item(({"wall","walls"}),
        "The walls are dark mahogany rough-hewn beams.\n");

    add_item(({"ceiling", "beam", "beams"}),"The ceiling and walls are made " +
        "from dark mahogany rough-hewn beams.\n");

    add_item(({"floor", "ground"}),"The floor is made from polished oak. " +
        "It is shiney and spotless.\n");

    add_item("sign", "Perhaps you could read it?\n");

    add_cmd_item("sign","read",
      "You may become a member of the Equestrian Society of Bree if you are " +
      "a horse lover and have rented a steed from the Bree Stables or are a " +
      "Noldor or in the Solamian Calvary. There are no membership fees of " +
      "any sort. The Society Lounge is to the south and is for members only. "+
      "If you <join now>, you will become a member of the Society and be " +
      "entitled to enter the Society Lounge. Upon joining you will receive " +
      "a riding crop as proof of membership. Should you ever lose your crop, "+
      "you can get a new one by typing <crop me> here.  If you ever wish to "+
      "leave the Society, come here and <abandon society>.\n");

    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STABLE_DIR + "/east_yard","north");
    add_exit(STABLE_DIR + "/club/board", "south",
        check_member);
}

void
init()
{
    ::init();
    add_action("do_join", "join");
    add_action("do_abandon", "abandon");
    add_action("do_crop", "crop");
}


public int
check_member()
{
    if(!TP->test_bit("Shire",FOURTH_GROUP,EQUESTRIAN_BIT))
    {
        write("You're not a member of the Equestrian Society.\n");
        return 1;
    }
    return 0;
}


int
do_join(string str)
{
    object crop;
    int i;
    string *souls, race;
    mapping steed_owners = ([ ]);

    if(str != "now")
    {
        write("Join when?\n");
        return 0;
    }

    if(TP->test_bit("Shire",FOURTH_GROUP,EQUESTRIAN_BIT))
    {
        write("You're already a member of the Equestrian Society.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());


    steed_owners = restore_map(STABLE_DIR + "/log/steed_owners");

    if (!steed_owners[TP->query_real_name()] &&
        TP->query_guild_name_race() != "Noldor of Imladris" &&
        TP->query_guild_name_occ() != "Solamnian Knights")
    {
        write("Only those who meet the requirements may join. Read the sign, "+
            "please.\n");
        return 1;
    }

    write("Welcome to the Equestrian Society of Bree.\n");
    write_file(EQUESTRIAN_LOG, TP->query_name()+ " joined " +
      extract(ctime(time()), 4, 15) + "\n");

    seteuid(getuid(TO));
    TP->set_bit(FOURTH_GROUP,EQUESTRIAN_BIT);
    crop = present("_equestrian_crop_", TP);
    if (!crop)
    {
        crop = clone_object(STABLE_DIR + "/club/t_crop");
        crop->move(TP,1);
        write("You get your fine black leather riding crop.\n");
        say(QCTNAME(TP) +
            " becomes an a member of the Equestrian Society of Bree.\n");
    }
    return 1;
}

int
do_abandon(string str)
{
    object crop;
    int result;
    object soul;

    if (str !="society")
    {
        write("Abandon what? Society?\n");
        return 1;
    }

    if(!(TP->test_bit("Shire",FOURTH_GROUP,EQUESTRIAN_BIT)))
    {
        write("You aren't a member of the Society.\n");
        return 1;
    }
    write("We hope you find your way back soon.\n");
    crop = present("_equestrian_crop_", TP);
    if (crop)
    {
        crop->remove_object();
        write("Your crop is taken away from you.\n");
    }
    say(QCTNAME(TP) + " leaves the Equestrian Society.\n");
    write_file(EQUESTRIAN_LOG, TP->query_name()+" left "+
      extract(ctime(time()), 4, 15) + "\n");
    TP->clear_bit(FOURTH_GROUP,EQUESTRIAN_BIT);
    TP->remove_equestrian_hobble_shadow();

    TP->remove_cmdsoul(EQUESTRIAN_SOUL);
    TP->update_hooks();
    return 1;
}

int
do_crop(string str)
{
    object crop;

    if (str != "me")
        return 0;

    if (!(TP->test_bit("Shire",FOURTH_GROUP,EQUESTRIAN_BIT)))
    {
        write("Only Equestrians may crop themselves here.\n");
        return 1;
    }

    crop = present("_equestrian_crop_", TP);

    if (crop)
    {
        write("You already have a crop.\n");
        return 1;
    }
    crop = clone_object(STABLE_DIR + "/club/t_crop");
    crop -> move(TP,1);
    write("You receive a fine black leather riding crop.\n");
    say(QCTNAME(TP)+" receives a riding crop.\n");
    return 1;
}

void
soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
        ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(EQUESTRIAN_SOUL);
    for (i = 0; i < sizeof(souls); i++)
    if (souls[i] != EQUESTRIAN_SOUL)
        ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}
