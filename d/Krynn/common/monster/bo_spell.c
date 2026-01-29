/* spellobject of the Bozak, created by Aridor, 25/11/93 */

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

string color;
int level;
object owner;

create_object()
{
    ::create_object();
    add_prop(OBJ_I_WEIGHT, 0);	/* 1 Kg is default */
    add_prop(OBJ_I_VOLUME, 0);	/* 1 l is default */
    add_prop(OBJ_I_VALUE, 0);		/* 0 is default */
    set_name("draconian_spellobject");
    set_no_show(1);
    color = ({"red","blue","green","white","black","gold","silver","bronze"})[random(8)];
    level = random(3) + 1;
    owner = previous_object();
}

spell_attack(object me, object enemy)
{
    owner = me;
    do_a_spell();
}

do_a_spell()
{
    int the_hit, res;
    object *ene;
    object toughluck;
    ene = owner->query_enemy(-1);
    if (ene != ({}))
    {
	/*someone has tough luck and is the victim of a spell*/
	toughluck = ene[random(sizeof(ene))];
	if (environment(toughluck) != environment(owner))
	    return;
	if (toughluck->query_prop(OBJ_M_NO_MAGIC_ATTACK))
	    return;
	the_hit = - random(20) - level * random(10) - level * random(10);
	/* does the player have some magically enhancing fire resistance items??*/
	res     = toughluck->query_magic_res(MAGIC_I_RES_FIRE) + toughluck->query_prop(OBJ_I_RES_FIRE);
	the_hit = the_hit - ((the_hit * res) / 100);
	toughluck->heal_hp((the_hit < 0) ? the_hit : 0 );
	owner->tell_watcher(QCTNAME(owner) + " mumbles a few strange words and " +
	  color + " sparks fly from his hand and burn " +
	  QTNAME(toughluck) + ".\n", toughluck);
	toughluck->catch_msg(QCTNAME(owner) +
	  " mumbles a few strange words and " +
	  color + " sparks fly from his hand " +
	  ((the_hit >= 0) ? "but you are not harmed.\n" : "and burn you!\n"));
	if (toughluck->query_hp() <= 0)
	    toughluck->do_die(owner);
    }
}


config_spell(object who, int lev, string col)
{
    level = lev; 
    color = col; 
    owner = who;

}
