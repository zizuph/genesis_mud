inherit "/std/object";
#include "../guild_defs.h"
#include <macros.h>

#define OLD_CMDSOUL                 "/d/Terel/cedric/guild/soul/soul"
#define OLD_SHADOW                  "/d/Terel/cedric/guild/Obj/m_shadow.c"

public void
create_object()
{
    set_name("orb");
    add_name("_minstrel_change_orb");
    set_short("swirling azure orb");
    set_adj(({"swirling","azure"}));
    set_long("This swirling azure orb sits on an elegant silver " +
        "frame. Any Minstrel who rubs or polishes it will find " +
        "themselves newly inspired by the Muses!\n");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_GET, "The orb is too big to pick up.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This orb is magical.\n", 75 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

int 
rub(string str)
{
    object  shadow, instrument, new_instrument;

    if ((str=="orb")||(str=="azure orb")) 
    {
        if (!MEMBER(this_player()))
        {
            notify_fail("You are not a Minstrel!\n");
            return 0;
        }

        if(!this_player()->query_old_cedric_minstrel_guild())
        {
            notify_fail("You rub the orb but it doesn't do anything, " +
                "as you have already transitioned to the " +
                "new Minstrel guild!\n");
            return 0;
        }

         setuid();
         seteuid(getuid());

         write("You rub the orb and feel your understanding of the " +
             "Muses shift!\n");
         say(QCTNAME(this_player())+ " rubs the swirling azure orb.\n");

         if(this_player()->query_skill(SG_INSTRUMENTAL) > 60)
             this_player()->set_skill(SG_INSTRUMENTAL, 60);
         if(this_player()->query_skill(SG_VOCAL) > 60)
             this_player()->set_skill(SG_VOCAL, 60);
         if(this_player()->query_skill(SG_READ_MUSIC) > 60)
             this_player()->set_skill(SG_READ_MUSIC, 60);
         if(this_player()->query_skill(SG_TUNE_REPAIR) > 60)
             this_player()->set_skill(SG_TUNE_REPAIR, 60);

         present("minstrel_song_book", this_player())->remove_object();
         instrument = present("minstrel_instrument", this_player());
         int damage = instrument->query_damage();
         string name = instrument->query_name();

         OLD_CMDSOUL->remove_spells(this_player());
         this_player()->remove_cmdsoul(OLD_CMDSOUL);
         this_player()->update_hooks();
         this_player()->remove_guild_lay();

         instrument->remove_object();

         shadow = clone_object(GUILDSHADOW);
         shadow->shadow_me(this_player(), "layman", "cleric", GUILD_NAME);
         this_player()->add_cmdsoul(GUILDSOUL);
         this_player()->update_hooks();

         new_instrument = clone_object(NEW_GUILDOBJ + "instrument");
         new_instrument->set_name(name);
         new_instrument->set_damage(damage);
         new_instrument->move(this_player(), 1);
         new_instrument->do_things();

         return 1;
    }

    notify_fail("Rub what?\n");
    return 0;
}

void
init()
{
   ::init();
   add_action(rub, "rub");
   add_action(rub, "polish");

}
