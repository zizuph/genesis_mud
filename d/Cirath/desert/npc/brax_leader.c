/*
 * made by: Yrgol
 * date: 2/2 - 02
 * File: /w/yrgol/test/regen_npc.c
 * Comment: Resists 1/3 of all the damage delt to him.
 *
 * Milashk: This is the basics, then you/we could fix
 * so that it sais a little nicer like as your short sword
 * leaves Agreblugs body the scar immediatly begins to heal.
 *
 * and if it's a bludgedon weap its more like, the body bumps
 * out again.. or whatever.. it can all be done..
 * but this is what you asked for.
 */

inherit "/std/monster";
inherit "/std/combat/humunarmed.c";
#include <wa_types.h>
#include <stdproperties.h>
#include <options.h>
#define DES_WEP "/d/Cirath/desert/wep/"
#include "/d/Kalad/defs.h"

int resist;  // The value of resistment

create_monster()
{
    set_adj("massive");
   add_adj("horned");
   set_race_name("braxat");
    set_short("massive horned braxat");
    set_long("Covered in a thick, scaly carapace, this creature "
    	+"is a horror to look at.  Its lizard like head has many "
    	+"hornlike protrusions jutting out from it, giving it a "
    	+"demonic appearance.  Thick squatty legs support this "
    	+"creature as it walks across the sand, while its thickly "
    	+"shelled back protects it from both the sun and attacks.  "
    	+"Its stands about 7 feet high, and slouches forward with "
    	+"its arms swinging low.  Its arms look like small trees, "
    	+"and appear easily capable of crushing a skull.\n");
    set_stats(({180,130,170,100,100,130}));
    add_prop(CONT_I_WEIGHT,90000);
    add_prop(CONT_I_HEIGHT,195);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_WEP_CLUB, 90);
    set_all_hitloc_unarmed(50);

    set_cchat_time(6);
    add_cchat("Me smash you to goo!");
    add_cchat("You want death, you come get!");

    set_cact_time(5);
    add_cact(({"roar","growl","smile grim"}));

}

void
arm_me()
{
    clone_object(DES_WEP+"d_club")->move(TO);
    command("wield all");
}

resist()
{
   if(resist)
      write("The wounds on the massive reptilian braxat close and "
      	+"quickly begin to heal.\n");
   this_object()->add_hp(resist);
}

void
cr_got_hit(int hid, int ph, object att,int aid, int dt, int dam)
{
   resist=dam/2;
   ::cr_got_hit();
   set_alarm(0.1,0.0,"resist");
   return;
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = this_object();
 

    if(random(8)) return 0;
    {
        ob =  FILTER_LIVE(all_inventory(environment(TO))) - ({ TO });

        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 300 + random(150);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 50;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, TO, -1);

	      how = "unnoticeably";
            if (hitresult[0] > 0)
                how == "barely";
            if (hitresult[0] > 10)
                how = "slightly";
            if (hitresult[0] > 20)
                how = "quite badly";
            if (hitresult[0] > 40)
                how = "very badly";
            if (hitresult[0] > 60)
                how = "to a crisp";
            ob[i]->catch_msg("The braxat's nostrils flare as it sucks in a "
            	+"huge breath of air.  An instant later it breathes out a "
            	+"large cloud of acid!\n");
            ob[i]->catch_msg("The acid clings to your skin, burning you "+
            	how +"!\n");
       tell_watcher(QCTNAME(ob[i]) + " is hit " + how + " by the acid "+
            "breath of the monstrous braxat!\n", ob[i]);


            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }
}


int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

