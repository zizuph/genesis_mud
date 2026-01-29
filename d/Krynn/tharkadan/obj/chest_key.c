/*
*    Key for ogre magi invisible chest
*/
#include "/d/Krynn/tharkadan/local.h"
inherit "/std/key";

void
create_key() 
{
    ::create_key();
    set_name("key");
    add_name("_ogre_magi_lair_key");
    set_short("obsidian key");
    set_adj("obsidian");
    set_long("This an key made from obsidian and carved with elaborate, " +
       "if rather sadistic, images and runes.\n");

    set_key(OGRE_MAGI_KEY);
    add_prop("_key_i_no_keyring",1); 

}
