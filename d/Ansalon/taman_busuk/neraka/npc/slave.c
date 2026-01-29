/* Ashlar, 24 May 97 - a random slave */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

private string *races = ({ "human", "half-elf", "dwarf", "gnome", "elf" });
private string *adjectives = ({ "young", "old", "middle-aged", "small",
  "scarred", "one-eyed", "sick", "starved" });

void
create_krynn_monster()
{
    int r,a,i;	

    r = random(sizeof(races));
    a = random(sizeof(adjectives));

    set_name("slave");
    add_name("neraka_slave");
    set_race_name(races[r]);
    set_adj(adjectives[a]);
    add_adj(races[r]);
    set_short(adjectives[a] + " " + races[r] + " slave");
    set_long("The " + short() + " looks very hungry and tired.\n");

    for(i=0; i<6; i++)
	set_base_stat(i, random(20) + 5);   /* 5-24 */
    set_skill(SS_DEFENCE, random(25) + 5);  /* 5-29 */
    set_skill(SS_WEP_KNIFE, random(25) + 5);

    i = query_average_stat();
    set_alignment(i*(i+20));
    set_knight_prestige(-i);

    set_all_attack_unarmed(15,20);
    set_all_hitloc_unarmed(5);

    if (!pointerp(query_leftover("heart")))
	add_leftover("/std/leftover","heart",1,0,0,1);

    if (!pointerp(query_leftover("eye")))
	add_leftover("/std/leftover","eye",2,0,0,0);

}

void
arm_me()
{
    seteuid(getuid());
    if(random(3))
	clone_object(NWEP + "spoon")->move(TO);
    if(random(3))
	clone_object(NARM + "rags")->move(TO);

    command("wear all");
    command("wield all");
}

