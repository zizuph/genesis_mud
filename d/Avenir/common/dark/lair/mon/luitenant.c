/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/monster";
#include "../dark.h"

public void
equip_me(void)
{
    clone_object(OBJ +"evil_spear")->move(TO);
    clone_object(OBJ +"helmet")->move(TO);
    clone_object(OBJ +"chainmail")->move(TO);
    clone_object(OBJ +"bshield")->move(TO);

    command("wear all");
    command("wield all");
}

public void
create_monster(void)
{
    setuid();
    seteuid(getuid());

    set_race_name("dark elf");
    add_name(({ "elf", "luitenant", "warrior" }));
    set_short("dark elf luitenant");
    set_pshort("dark elf luitenants");
    set_long("These evil creatures are the opposers of all light " +
	"and truth. They seek utter darkness for the world. They are pale "+
	"beings with dark hair, their beauty being that of the "+
	"shadows. They are wicked things. "+
	"This one being a luitenant, a great warrior.\n");

    set_stats(({ 66, 72, 68, 45, 45, 50}));
    set_alignment(-266);

    set_skill(SS_PARRY,		75);
    set_skill(SS_DEFENCE,	75);
    set_skill(SS_WEP_SWORD,	78);
    set_skill(SS_WEP_POLEARM,	80);
    set_skill(SS_SPELLCRAFT,	60);

    set_all_hitloc_unarmed(25);

    equip_me();
}
