/* 
 * Murseka object - controls subloc and shadow
 */
inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../../guild/local.h"

#define DEBUGTELL(x) find_player("karath")->catch_msg(x)
#define MURSEKA_SUBLOC "wohs_murseka_subloc"
#define MAGOBJDIR "/d/Krynn/wayreth/magic/obj/"

object affected, sh;

void
create_object()
{
    add_name("mag_murseka_obj");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical object controlling the murseka " +
      "shadow of the affected. provides immunity to mundane attacks.\n");

    set_no_show();
}

public int
remove_myself()
{
    tell_object(affected, "Your skin loses it's sheen, and you feel "+
	"less protected.\n");
    sh->remove_murseka_shadow();
    affected->remove_subloc(MURSEKA_SUBLOC);
    return 1;
}

public void
enter_env(object dest, object old)
{
    affected = dest;
    if(sh = clone_object(MAGOBJDIR + "murseka_shadow"))
      {
	sh->shadow_me(affected);
    	affected->add_subloc(MURSEKA_SUBLOC, TO);
      }
}

public void
notify_dispel_magic(object ob)
{
    remove_myself();
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "Your hands have a chilling aura.\n";

    return capitalize(PRONOUN(me)) + "'s hands have a chilling "+
	"aura around them.\n";
}

/* This called from the glove shadow to do fire damage
 * to opponents when a successful unarmed attack is made
 * while wearing the gloves.
 */
int special_damage(int aid, string hdesc, int phurt, object enemy, int phit,
    int dam)
{
  int hurt, res, fire_dam;
  object wearer;
  string with, where, how, what, owhat, burn;

  /* make sure we hit with a flaming glove */
  if (!(aid & murseka_attack_id))
  {
    return 0;
  }

  if (!(wearer = query_worn()))
  {
    return 0;
  }

  /* calculate damage, taking fire resistance into account */
  res = 100 - enemy->query_magic_res(MAGIC_I_RES_FIRE);
  fire_dam = MAX(0, (random(50) + 1) * res / 100);
  hurt = enemy->hit_me(fire_dam, MAGIC_DT, wearer, -1)[2];

  if (hurt < 1)
  {
    return 0;
  }

  /* give an attack description */
  with = (aid == W_RIGHT ? " right hand" : " left hand");

  where = " the " + hdesc + " of ";

  switch (phurt)
  {
    case 0..4:
	how = "";
	what = "tickle";
	owhat = "tickles";
	break;
    case 5..9:
	how = "";
	what = "graze";
	owhat = "grazes";
	break;
    case 10..19:
	how = "";
	what = "hurt";
	owhat = "hurts";
	break;
    case 20..29:
	how = ", rather bad";
	what = "hurt";
 	owhat = "hurts";
	break;
    case 30..49:
	how = ", very bad";
	what = "hurt";
	owhat = "hurts";
	break;
    case 50..69:
	how = ", very hard";
	what = "smash";
	owhat = "smashes";
	break;
    case 70..89:
	how = ", with a bone crushing sound";
	what = "smash";
	owhat = "smashes";
	where = " ";
	break;
    default:
	how = "";
	what = "massacre";
	owhat = "massacres";
	where = " ";
  }

  switch (hurt)
  {
    case 1..10:
        burn = " singeing ";
        break;
    case 11..30:
        burn = " searing ";
        break;
    case 31..70:
        burn = " blistering ";
        break;
    default:
        burn = " charring ";
        break;
  }

  if (interactive(wearer))
  {
    wearer->catch_msg("You " + what + where + enemy->query_the_name(wearer) +
        " with your" + with + how + ", your glove" + burn + 
        enemy->query_possessive() + " flesh.\n");
  }

  if (interactive(enemy))
  {
    enemy->catch_msg(QCTNAME(wearer) + " " + owhat + " your " + hdesc +
	    " with " + wearer->query_possessive() + with + how +
            ", " + wearer->query_possessive() + " glove" + burn + 
            "your flesh.\n");
  }

  wearer->tell_watcher(QCTNAME(wearer) + " " + 
      owhat + where + QTNAME(enemy) + " with " + 
      wearer->query_possessive() + with + how + ", " +
      wearer->query_possessive() + " glove" + burn + 
      enemy->query_possessive() + " flesh.\n", enemy);

  return 1;
}
