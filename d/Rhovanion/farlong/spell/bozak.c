/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/sys/money.h"

#define SPELL_OBJECT  OBJ + "bo_spell"

inherit M_FILE


/*prototype*/
void hurt_everyone_around();


/*the spellobject*/
object sp;


/*army color the bozak belongs to */
string color = "blue";

/*put bozak into another army :-) */
set_color(string new_color)
{
    color = new_color;
}

int equip_level;

#include "arm_me.h"

int level;

void
create_monster()
{
    int i, j = random(4) + 3; /* j is the level of the draconian */
    string str;
    level = j;

    set_name("bozak");
    set_race_name("draconian");
    add_prop(OBJ_I_RES_FIRE, 80);
    add_prop(OBJ_I_RES_ACID, 80);
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 100, "transmutation"}));

#include "level_me.h"

    set_adj("broadfaced");
    set_long(BS("This draconian has a broad reptilian face and his eyes look "
        +    "like darts can shoot from them. " + str, SL));


    for(i=0; i<6; i++)
        set_base_stat(i, j * 13 + random(10) + 1);
    set_skill(SS_DEFENCE,     j * 16 + random(5) + 5);
    set_skill(SS_PARRY,       j * 15 + random(5) + 5);
    set_skill(SS_WEP_SWORD,   j * 15 + random(5) + 5);
    set_skill(SS_WEP_KNIFE,   j * 15 + random(5) + 5);
    set_skill(SS_WEP_CLUB,    j * 15 + random(5) + 5);
    set_skill(SS_WEP_JAVELIN, j * 15 + random(5) + 5);
    set_skill(SS_WEP_POLEARM, j * 15 + random(5) + 5);
    set_skill(SS_WEP_AXE,     j * 15 + random(5) + 5);

    i = query_average_stat();
    i = i*i/10;
    set_alignment((i>950) ? (-1000) : (-i - 50));
    set_knight_prestige((i > 1600) ? (2000) : (i + 400));

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);

    set_act_time(3);
    add_act("screams");
    add_act("stare");
    add_act("emote shows you his claws.");
    add_act("say What are you doing here?");
    add_act(({"say Get lost!", "laugh"}));
    add_act("emote shows you the finger, or rather, his middle claw.");
    add_act("frown");
    add_act("grin");
    add_act("giggle");
    add_act("twiddle");
    set_cact_time(10);
    add_cact("say You really think you can defeat me?\n");
    add_cact("say Ahhh, now I can test my battle skill.\n");
    add_cact("say I didn't even feel that!\n");
    add_cact("say Is that all you can do?\n");
    add_cact("say Don't take it personally but I'll kill you.\n");
    add_cact("grin");
    
    ::create_monster();

    if (IS_CLONE)
        call_out("arm_me",3 , j + 2);/*modify the equipment to the level*/

}


public void
attacked_by(object ob)
{  
    ::attacked_by(ob);
    seteuid(getuid(TO));
    command("say That was your last mistake in this life, " + ob->query_race_name() + "!");
    sp = clone_object(SPELL_OBJECT);
    sp->config_spell(TO,level, color);
      add_prop(LIVE_O_SPELL_ATTACK, sp);
      call_out("reload",random(15) + 10);
}


reload()
{
    add_prop(LIVE_O_SPELL_ATTACK, sp);
    call_out("reload", random(15) + 22);
}


public void
do_die(object killer)
{

	if (query_hp() > 0 || query_wiz_level())
		return;
	if (!killer)
		killer = previous_object();

	if (!query_combat_object()) combat_reload();
	query_combat_object()->cb_death_occured(killer);
	killer->notify_you_killed_me(this_object());

	command("drop all");
        say("The skin and flesh of the draconian dries out and crumbles from the bones!\n");
	say("BANG! The bones of the draconian explode!\n");
	hurt_everyone_around();

        this_object()->remove_object();
}


void
hurt_it(object livin)
{
    object cb_obj = livin->query_combat_object();

    int *hitlocs = cb_obj->query_hitloc_id();
    mixed *hloc, *ac;
    int i, hits, sum = 0;
    for (i = 0; i < sizeof(hitlocs); i++)
      {
	hloc = cb_obj->query_hitloc(hitlocs[i]);
	ac = hloc[0];
	if (!pointerp(ac))
	  ac = ({ ac }); /*set the impale (= 0) hitlocation value; shards impale! */
	/* hloc[1] is the percentage of the hits for the location*/
	sum += hloc[1] * ac[0];
      }
    sum /= 100;/*the sum of perc_hit = 100*/
    hits = - level * random (20) - 50;
    hits -= sum;
    hits = ((hits > 0) ? 0 : hits);
    if (livin->query_hp() < hits)
      hits = -random(livin->query_hp() + 1);
/*we are very friendly here! Especially so newbies won't die just TOO fast...*/
    livin->heal_hp(hits);
    tell_object(livin,"You are struck by shards of bone. " + 
		((hits >= 0) ? "You are not harmed though.\n" : "Ouch, that hurts.\n"));
    livin->do_die(this_object());
}


void
hurt_everyone_around()
{
    int i;
    object *things;
    seteuid(getuid(this_object()));
    things = all_inventory(environment(this_object()));
    for (i = 0; i < sizeof(things); i++)
      if ((things[i]->query_prop(LIVE_I_IS)) && (things[i] != this_object()))
	/* don't hurt myself :-) I'm dead, right? */
	hurt_it(things[i]);
}

