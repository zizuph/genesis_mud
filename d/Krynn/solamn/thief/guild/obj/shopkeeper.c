/* The solamnian knights shopkeeper
 * modified for the thief fence by Aridor */

#include "../guild.h"
inherit M_FILE

void
create_krynn_monster()
{
    set_name("almath");
    set_living_name("almath");
    set_short("Almath");
    add_name("fence");
    add_name("shopkeeper");
    set_gender(1);
    set_long("You recognize Almath, the fence of the Cabal of Hiddukel.\n");
    set_race_name("human");
    default_config_mobile(90);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);

    set_alignment(-100);
    set_knight_prestige(800);

    ALWAYSKNOWN;
}


void
attacked_by(object ob)
{
    ::attacked_by(ob);
    tell_room(environment(ob), "The fence easily steps out of your way and " +
	      "disappears down the stairs.\n");
      this_object()->remove_object();
}

