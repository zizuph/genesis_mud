/*
 * 2017-10-18 Zignur modified members_only to let the wolf pass
 * into the guild
 *
 */
inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma strict_types
#pragma save_binary
#define IS_MEMBER_FANG(x)    (x->query_guild_member("Red Fang"))


object obj;


void
ftrans(object ob)
{
    set_alarm(2.0,0.0,"ftrans2",ob);
}
void
ftrans2(object ob)
{
    object sh;
    sh = clone_object(FANG_SHADOW);
    sh->shadow_me(ob,GUILD_TYPE,GUILD_STYLE,GUILD_NAME);
}

public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())
    {
        /* Is a member, pass through as normal */
       return 0;
    }
    
    /* Zignur 2017-10-17 Make it so the wolf can move around freely. */    
    if (this_player()->query_name("_rf_wolf_"))
    {
        /* Is a a red fang wolf, allow him to move along */
        return 0;
    }
    

    write("You are pushed back by a bunch of large, burly goblins.\n");
    say(QCTNAME(TP)+" tries to go into the hall, but is pushed black "+
    "by a bunch of large, burly goblins.\n");
    return 1;
}
public int
fang_members_only()
{
    if (IS_MEMBER_FANG(this_player()) || this_player()->query_wiz_level())

    {
        /* Is a member, pass through as normal */
       return 0;
    }
    

    write("You are pushed back.\n");
    say(QCTNAME(TP)+" tries to go into the hall, but is pushed back.\n");
    return 1;
}


void
create_room()
{
    ::create_room();
    INSIDE;

    set_short("The headquarters of the Red Fang");

    set_long("\n   You are now in the main headquarters of the Red Fang. "+
    "The smooth rock walls around you shine in the dim torchlight. There "+
    "is a large red banner hanging from the low ceiling.\n"+
    "   In the center, there is a large stone table, behind which "+
    "sits a rather mean and brutally scarred goblin. Many chairs "+
    "surround the large table, while four exits lead further into "+
    "this dark lair.\nTo join: \"sign in\". To leave \"leave guild\".\n");
    add_item("banner","Several words have been written upon it.\n");
    add_cmd_item("banner","read","Here you may join or leave the "+
    "notorious, revolutionary army known as the Red Fang. Ask "+
    "Brutakis for more information.\n");

    add_item("chairs","They are set around the table and are made of "+
    "black oak.\n");

    add_exit(CPASS(goblin/g19),"north",0,-1,-1);
    add_exit(FANG_DIR(rooms/train),"west", members_only);
    add_exit(FANG_DIR(rooms/plan_room),"east", members_only);
    add_exit(FANG_DIR(rooms/hall),"south", members_only);
    add_exit(FANG_DIR(rooms/po),"post", fang_members_only);
    add_exit("/d/Raumdor/guilds/fang/room/stable","in", fang_members_only);
    obj = clone_object(FANG_DIR(obj/brutakis));
    obj->arm_me();
    obj->move_living("M",TO);
    clone_object(FANG_DIR(obj/table))->move(TO,1);
}

void
init()
{
   ::init();
   add_action("join", "sign");
   add_action("my_leave", "leave");
   add_action("update","update");
   add_action("history","read");
}

int
history(string str)
{
    string file;
    if(str != "book")
    {
        NF("Read what? The book?\n");
        return 0;
    }
    write("You read the book on the table.\n");
    file = read_file(FANG_DIR(doc/help_history));
    TP->more(file,0);
    return 1;
}

int
join(string str)
{
    object shadow,badge;

    if(str == "in")
    {
        if(TP->query_race_name() != "goblin")
        {
            NF("Only Goblins may join our force!\n");
            return 0;
        }
        if(TP->query_alignment() > 600)
        {
            NF("We are too ruthless for you.\n");
            return 0;
        }
        if (TP->query_guild_member(GUILD_TYPE))
        {
            NF("You cannot be a member of two race guilds!\n");
            return 0;
        }
        shadow = clone_object(FANG_SHADOW);
        NF("How odd. For some reason you cannot join us.\n");
        if(shadow->shadow_me(TP,GUILD_TYPE, GUILD_STYLE,GUILD_NAME) !=1 )
        {
            shadow->remove_object();
            return 0;
        }
        write("You sign your name and become a member of the Red Fang.\n");
        say(QCTNAME(TP) + " signed in to join the Red Fang.\n");
        log_file("fang",TP->query_real_name()+" joined "+
        extract(ctime(time()),4,15)+".\n");
        TP->add_cmdsoul("/d/Kalad/common/guilds/red_fang/commands/fang_soul_temp");
        TP->update_hooks();
        TP->clear_guild_stat(SS_RACE);
        badge = present("_fang_", TP);
        if(!objectp(badge))
        {
            badge = clone_object(FANG_DIR(obj/f_badge));
            badge->move(TP);
            write("You receive your badge of honor.\n");
        }
        return 1;
    }
    return 0;
}

int
my_leave(string str)
{
    object badge;

    if (str != "guild")
    {
        write("What do you wish to leave?\n");
        return 1;
    }

    if(TP->query_guild_name_race() != GUILD_NAME)
    {
        NF("You cannot leave a guild you are not a member of.\n");
        return 0;
    }
    if(TP->remove_guild_race())
    {
        write("You are no longer a member of the Red Fang.\n");
        badge = present("_fang_", TP);
        if(objectp(badge))
        {
            badge->remove_object();
            write("Your badge is ripped off you.\n");
            say(QCTNAME(TP) + " leaves the Red Fang.\n");
            log_file("fang",TP->query_real_name()+" left   "+
            extract(ctime(time()),4,15)+".\n");
        }
        TP->remove_cmdsoul("/d/Kalad/common/guilds/red_fang/commands/fang_soul_temp");
        TP->clear_guild_stat(SS_RACE);
        TP->update_hooks();
        if (this_player()->query_default_start_location() == "/d/Kalad/common/guilds/red_fang/rooms/start")
        {
             this_player()->set_default_start_location(0);
        }
        return 1;
    }
    else
      write("Because of an error, you remain with us.\n");
    return 1;
}

int
update(string str)
{
    object badge,shadow;

    if (str != "membership")
    {
        NF("Update what?\n");
        return 0;
    }

    if(!IS_MEMBER(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    badge = present("_fang_",TP);
    if(!objectp(badge))
    {
        write("Adding new badge.\n");
        clone_object(FANG_DIR(obj/f_badge))->move(TP);
    }
    write("Updating shadow.\n");
    shadow = clone_object(FANG_SHADOW);
    TP->remove_guild_race();
    if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
        write("Lost shadow, contact wizard.\n");
        shadow->remove_object();
    }
    TP->add_cmdsoul("/d/Kalad/common/guilds/red_fang/commands/fang_soul_temp");
    TP->update_hooks();
    write("Done!\n");
    return 1;
}
