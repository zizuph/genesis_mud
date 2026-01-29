#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

public void test_ranger(object player);

create_room()
{
    set_short("Resting room");
    set_long(BS("As you enter this room you think you have entered a forest "+
    "in moonlight. "+
    "The pillars of this room have been sculpted into the semblance of "+
    "trees. Softened light from hidden light sources gives the room a "+
    "peaceful atmosphere. Hidden discreetly behind the pillars are some "+
    "alcoves. "+ 
    "Rangers may type 'start here' to select this as the "+
    "place where they start up when entering the game.\n"));
    add_item("alcoves","Rangers are resting in them, tired after hard work.\n");    add_item("pillars",BS("They are beautifully sculpted, you almost have to "+
    "touch them to realise that they are not real trees.\n"));
    add_item(({"light sources","light"}),BS("You can't see the source of the "+
    "light, but you feel at rest in this room.\n"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

    add_exit(RANGER_NORTH_DIR+"r_corridor","south",0);
}

init()
{
    ::init();
    add_action("start_here","start");
}

start_here(string str)
{
    if (str != "here")
    {
        NF("Start where?\n");
        return 0;
    }
    seteuid(getuid(TO));
    if (TP->query_wiz_level()) return 0;
    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS) 
    {
        write(BSN("You may not change your start location, since the Council of "+
		  "Rangers has punished you with limited access to the "+
		  "guildhouses."));
	return 1;
    }
    if (TP->query_guild_name_occ()=="Rangers of the North")
    {
        TP->set_default_start_location(file_name(TO));
        write("From now on you will start here when entering the game.\n"); 
        return 1;
    }
    else
    {
        NF("But you are not one of the Rangers of the North!\n");
        return 0;
    }
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);

   if (!living(ob) || !interactive(ob))
      return;
   if (!objectp(from))
      set_alarm(2.0, 0.0, &test_ranger(ob));
}

public void
test_ranger(object player)
{
   if (!objectp(player))
      return;

    if (player && player->query_guild_name_occ() != "Rangers of the North")
   {
      player->catch_msg("You may not start here anymore.\n"
                      + "The North Company has been purged.\n"
                      + "A strong but invisible arm grabs you, "
                      + "and takes you somewhere else.\n");
      player->set_default_start_location(player->query_def_start());
      player->move_living("M",player->query_def_start(),1,0);
   }
}
