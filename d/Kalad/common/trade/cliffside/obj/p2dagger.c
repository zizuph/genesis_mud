/*
 * Coded by: unknown
 *
 * This weapon is wielded by penance in Kalad, the weapon was designed to
 * increase defence and parry of the wielder. This effect was added in a
 * poorly fashion and did not work.
 * 
 * Modified by Carnak:
 *  - I fixed the bug with the skills and added comments/function 
 *      descriptors. 
 *
 *  20210730 Meton Added logging, as player reported getting
 *      permanently panicked. Could be an issue with wield/unwield.
 */

 inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <formulas.h>

// Global Variables
static int      added_skill1, added_skill2;


/*
 * Function name:   create_weapon
 * Description:     Basic weapon construct
 * Arguments:       None
 * Returns:         Nothing
 */
void
create_weapon()
{
    ::create_weapon();

    set_name(({"dagger", "_penance_dagger2"}));
    add_adj(({"parrying","long"}));
    set_short("long parrying dagger");
    set_long("This long dagger is the type used for parrying. Nonetheless, "
      +"it looks like a potent weapon for stabbing in combat. It "
      +"has a glow to it, as if magical.\n");
    set_hit(30);
    set_pen(25);
    set_hands(W_ANYH);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_wf(TO);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO,"This is enchanted dagger that has been "
      +"magically augmented to have a higher hit and pen than "
      +"a normal weapon. It is also able to bestow upon the "
      +"wielder an increased parry/defence skill. To be able to "
      +"wield it, though, a 75 in SS_KNIFE, 80+ dis, and 100+ dex "
      +"has to be possessed. Without it, the weapon causes an "
      +"increase in panic.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This weapon seems to be able to do "
	+"a nice amount of damage, and also seems to be able to "
	+"help ward off attacks.\n", 55}));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
} /* create_weapon */

/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 *                Note: this routine does not actually exist in /std/weapon.
 *                      A trick is used to fool the document maker.
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed
unwield(object obj)
{
    this_player()->set_skill_extra(SS_PARRY, 
        this_player()->query_skill_extra(SS_PARRY) - added_skill1);
    added_skill1 = 0;
    
    this_player()->set_skill_extra(SS_DEFENCE,
        this_player()->query_skill_extra(SS_DEFENCE) - added_skill2);
    added_skill2 = 0;

    log_file("p2dagger", ctime(time()) + " "+
    "" + this_player()->query_real_name() + " had skills removed.\n");

    return 0;
} /* unwield */

/* 
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 *                Note: this routine does not actually exist in /std/weapon.
 *                      A trick is used to fool the document maker.
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */
mixed
wield(object what)
{
    int     parry, defence;
    
    if (this_player()->query_skill(SS_WEP_KNIFE) < 75 ||
        this_player()->query_base_stat(SS_DIS) <= 80 ||
        this_player()->query_base_stat(SS_DEX) <= 100)
    {
        this_player()->add_panic(random(100) - 5);
        
        log_file("p2dagger", ctime(time()) + " "+
        "" + this_player()->query_real_name() + "had panic added\n");

        return "You fail to control the power of the dagger.\n";
    }
    
    write("You manage to control the dagger.\n");
	
    parry   = this_player()->query_skill(SS_PARRY);
    defence = this_player()->query_skill(SS_DEFENCE);
    
    added_skill1 = (5 + (parry / 8));
    added_skill2 = (5 + (defence / 10));
    
    if((parry + added_skill1) > 100)
        added_skill1 = 100 - parry;
    
    if ((defence + added_skill2) > 100)
        added_skill2 = 100 - defence;
    
    this_player()->set_skill_extra(SS_PARRY, 
        this_player()->query_skill_extra(SS_PARRY) + added_skill1);
        
    this_player()->set_skill_extra(SS_DEFENCE,
        this_player()->query_skill_extra(SS_DEFENCE) + added_skill2);
    
        log_file("p2dagger", ctime(time()) + " "+
        "" + this_player()->query_real_name() + " got skills.\n");

    return 0;
} /* wield */
