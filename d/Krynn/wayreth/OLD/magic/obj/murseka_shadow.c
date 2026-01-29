/*   Igneous' immune from non-magical attacks shadow
 *
 *  Does what it's named after ;)
 *  All attacks done by non-magical damage types will not effect the 
 *  person with this shadow, unless the weapon is a magical one.
 *
 */
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#define DEBUG(x) find_player("karath")->catch_msg(x)

static object murseka;

void remove_murseka_shadow()
{
  remove_shadow();
}

int query_murseka_shadow() { return 1; }

void set_murseka_ob(object ob) { murseka = ob; }

object query_murseka_ob() { return murseka; }

/* Called from the combat sys when we make an unarmed attack */
int cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
  if (!mursekas)
  {
    remove_shadow();
    return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
  }

  /* If the unarmed attack has done more than 20 hps damage and the
   * attack is done with the right or left hand, we call a function
   * in the mursekas to do special damage.  Returning 1 disables the
   * combat system's normal handling of the remainder of the unarmed
   * attack; the special_damage() function in the mursekas takes care
   * of combat messages, etc.
   */
  if ((phurt >= 0) && (dam > 10) && (aid & W_BOTH) && 
      mursekas->special_damage(aid, hdesc, phurt, enemy, phit, dam))
  {
    return 1;
  }

  return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

void
remove_takadek_shadow()
{
    remove_shadow();
}
