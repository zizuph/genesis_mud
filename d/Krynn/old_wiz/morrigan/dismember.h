/* Dismemberment modification for swords by Morrigan, 5/12/97 */
#include <files.h>
#include <stdproperties.h>
#include <macros.h>


/* Function name: get_message
* Description  : Returns one of a few random messages.
* Arguments    : me = attacker
*                enemy = enemy
* Returns      : String array with messages for attacker, enemy, and
*                watchers.
*/
string *get_message(object me, object enemy)
{
    string *mes;
    object weapon = this_object();

    switch(random(3))
    {
    case 2:
	mes = ({ "With a mighty swing of your "+weapon->short()+", you ",
	  "With a mighty swing of "+POSSESSIVE(me)+" "+
	  weapon->short()+", "+me->query_the_name(enemy)+" ",
	  "With a mighty swing of "+POSSESSIVE(me)+" "+
	  weapon->short()+", "+QTNAME(me)+" " });
	break;
    case 1:
	mes = ({ "With tremendous force behind the blow of your "+
	  weapon->short()+", you ", "With tremendous force behind "+
	  "the blow of "+POSSESSIVE(me)+" "+ weapon->short()+", "+
	  me->query_the_name(enemy)+" ", "With tremendous force behind "+
	  POSSESSIVE(me)+" "+weapon->short()+", "+QTNAME(me)+" " });
	break;
    default:
	mes = ({ "In a vicious strike of your "+weapon->short()+", you ",
	  "In a vicious strike of "+POSSESSIVE(me)+" "+
	  weapon->short()+", "+QTNAME(me)+" ", "In a vicious "+
	  "strike of "+POSSESSIVE(me)+" "+weapon->short()+", "+
	  QTNAME(me)+" " });
    }
    return mes;
}


/*
* Function name: findcorpse
* Description  : Finds the appropriate corpse.
* Arguments    : Name of killed and killer.
* Returns      : Object corpse.
*/
object findcorpse(string killed, string killer)
{
    object *stuff = all_inventory(environment(query_wielded()));
    int i, index, most_recent, ob_num;

    set_this_player(this_interactive());
    /* get all corpses */
    stuff = filter(stuff, &operator(==)(CORPSE_OBJECT) @
      &function_exists("create_container"));
    /* get all corpses with the right name */
    stuff = filter(stuff, &->id("corpse of " + killed));
    /* get all corpses killed by the right person */
    stuff = filter(stuff, &operator(==)(killer) @ &operator([])(,0) @
      &->query_prop(CORPSE_AS_KILLER));


    most_recent = 0;
    index = -1;
    for (i = 0; i < sizeof(stuff); i++)
    {
	if (ob_num = atoi(OB_NUM(stuff[i])) > most_recent)
	{
	    most_recent = ob_num;
	    index = i;
	}
    }

    if (index > -1)
    {
	return stuff[index];
    }

    return 0;
}


/*
* Function name: did_hit
* Description:   Tells us that we hit something. Should produce combat
*                messages to all relevant parties. If the weapon
*                chooses not to handle combat messages then a default
*                message is generated.
* Arguments:     aid:   The attack id
*                hdesc: The hitlocation description.
*                phurt: The %hurt made on the enemy
*                enemy: The enemy who got hit
*                dt:    The current damagetype
*                phit:  The %success that we made with our weapon
*                dam:   The actual damage caused by this weapon in hit points
* Returns:       True if it handled combat messages, returning a 0 will let
*                the normal routines take over
*/
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int
  dam)
{
    object corpse, me = query_wielded(), part;
    string *str, *message, tmp;
    int i;

    if (dam < enemy->query_hp() || !enemy->query_humanoid())
	return 0;

    /* Set a 50% chance to dismember the enemy on a death blow */
    if (!random(100))
	return 0;

    corpse = findcorpse(L(enemy->query_name()), L(me->query_name()));
    find_living("morrigan")->catch_msg("DEBUG: corpse = "+corpse+"\n");

    /* DEBUGGING ONLY */
    find_living("morrigan")->catch_msg("Hdesc - "+hdesc+"\n");

    switch(hdesc)
    {
    case "head":
	str = ({ "behead "+enemy->query_the_name(me)+".", "beheads you.",
	  "beheads "+QTNAME(enemy)+"." });
	break;
    case "legs":
	str = ({ "chop off one of "+enemy->query_the_name(me)+"'s legs.",
	  "chops off one of your legs.", "chops off one of "+
	  QTNAME(enemy)+"'s legs." });
	break;
    case "right arm":
	str = ({ "sever "+enemy->query_the_name(me)+"'s right arm.",
	  "severs your right arm.", "severs "+QTNAME(enemy)+"'s "+
	  "right arm." });
	break;
    case "left arm":
	str = ({ "sever "+enemy->query_the_name(me)+"'s left arm.",
	  "severs your left arm.", "severs "+QTNAME(enemy)+"'s "+
	  "left arm." });
	break;
    case "body":
	return 0;
    }

    message = get_message(me, enemy);
    me->catch_msg(message[0]+str[0]+"\n");
    enemy->catch_msg(message[1]+str[1]+"\n");
    me->tell_watcher(message[2]+str[2]+"\n", enemy);

    enemy->heal_hp(-dam);
    enemy->do_die(me);

    switch(hdesc)
    {
    case "head":
	corpse->set_short("headless "+corpse->query_short());
	corpse->remove_leftover("scalp");
	corpse->remove_leftover("skull");
	part = clone_object("/std/leftover");
	part->leftover_init("head", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "legs":
	corpse->set_short("legless "+corpse->query_short());
	corpse->remove_leftover("thighbone");
	part = clone_object("/std/leftover");
	part->leftover_init("leg", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "right arm":
	corpse->set_short("armless "+corpse->query_short());
	part = clone_object("/std/leftover");
	part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "left arm":
	corpse->set_short("armless "+corpse->query_short());
	part = clone_object("/std/leftover");
	part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    }
    return 1;
}

