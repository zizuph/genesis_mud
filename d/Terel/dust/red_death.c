/* Chatting monster */

inherit "/std/monster";

create_monster()
{
    set_name("Red Death");
    add_name("death");
    add_name("red death");
    add_name("ghost");
    set_adj("Red");
    set_short("Red Death");
    set_long("This is the Red Death. He watches you suspiciously.\n");
    default_config_npc();
    set_stats(({500,500,500,500,500,500}));
    set_hp(300000);

    set_chat_time(7);
    add_chat("Thou shall praise your real master, mortal");
    add_chat("Thou shall sacrifice to please the ruler of life");
}

