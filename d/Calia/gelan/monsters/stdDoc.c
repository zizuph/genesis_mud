/* 	this is a monster of the town Gelan

    coder(s):   Merlin

    history:    21. 9.94  created               Merlin

    purpose:    stanard doctor for all doctors in the hospital

    weapon:     none
    armour:     none

    objects:    none

    quests:     none
    special:    make the healing, curing, operations

    to do:      

    bug:        none known
*/

#include "monster.h"
inherit STD_GUARD;
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


#define LOG "doctor.log"

/* the cost for cure
 *
 *        max hp cured  *  CURE_HP
 *      *
 *        docQual
 *
 * in coppers
 *
 */

int costHp = 10;

/* the quality of the doc
 *
 *    the chance for failure with the operation is
 *
 *                    1 - hp / maxHp
 *
 *    for example:  1 current hp with 1000 max hp means chance for failure
 *                  of 99.9 %
 *                  500 current hp of 1000 means 50 % chance
 *
 *    to determine the chance for failure, it's adjusted with the
 *    quality of the doc
 *
 *                    (1 - hp / maxHp) * docQual
 *
 *    example above with DOC_QUAL = 0.5 : 49.9 % / 25 %
 *
 *    Note: Failure does not mean death, but loss of hps, the chance for death is
 *          1 / hp * (1 - hp / maxHp) * docQual
 *
 *          example above: 49.9 % / 0.05 %
 *
 *
 *
 */
float docQual = 1.0;

/*
 * The following is the diagnose the doctors give, they are
 * similar for all doctors
 *
 */

string *diagnose =   ({
                       "Well, to be honest, a cure in this situation "
                     + "is almost a miracle. I will try with some special "
                     + "Voodoo practice.\n",
                       "Hmm, you are almost dead. A cure is hard, but I "
                     + "can try with some spiritual sining",
                       "This is a serious injury you have there. Your "
                     + "blood seems to be in disorder. You will need a "
                     + "radical blood drain. We have to replace this "
                     + "bad blood.\n",
                       "Oh, this is serious. But some time with several "
                     + "leeches will certainly do.\n",
                       "Hmm, it's not too bad. Let's try some small bleed.\n",
                       "Well, your injuries are not too bad. I think an "
                     + "ointment will do.\n",
                       "Ah, this healing is not a big deal, we'll just "
                     + "use some acupuncture are you are as new.\n"
                     });

string *riskDesc = ({  
                   "none",
                   "almost none",
                   "extermely low",
                   "very low",
                   "low",
                   "rather low",
                   "medium",
                   "rather high",
                   "high",
                   "very high",
                   "extremely high",
                   "rather deadly",
                   "deadly",
                   "very deadly",
                   "extremely deadly",
                   "certain death"
                   });


/*
 * The following array contains the messages that are given throughout the
 * cure. The first array contains the messages given when the cure will
 * be successfull (cureSucc), the second where the cure will fail (cureFail)
 * It does not matter how many strings are there in each subarray, but the number
 * of the arrays has to be equal to the number of strings in the diagnose
 * array.
 */

mixed *cureSucc = ({
                     ({
                       "1 succ",
                       "2 succ",
                       "3 succ",
                       "4 succ"
                     }),
                     ({
                       "A succ",
                       "B succ",
                     }),
                     ({
                       "a succ",
                       "b succ",
                       "c succ",
                     }),
                     ({
                       "succ 1",
                       "succ 2",
                       "succ 3",
                       "succ 4",
                       "succ 5",
                       "succ 6",
                     }),
                     ({
                       "succ"
                     }),
                     ({
                       "ok 1",
                       "ok 2",
                       "ok 3",
                       "ok 4"
                     }),
                  });

mixed *cureFail = ({
                     ({
                       "1 fail",
                       "2 fail",
                       "3 fail",
                       "4 fail"
                     }),
                     ({
                       "A fail",
                       "B fail",
                     }),
                     ({
                       "a fail",
                       "b fail",
                       "c fail",
                     }),
                     ({
                       "fail 1",
                       "fail 2",
                       "fail 3",
                       "fail 4",
                       "fail 5",
                       "fail 6",
                     }),
                     ({
                       "fail"
                     }),
                     ({
                       "yuk 1",
                       "yuk 2",
                       "yuk 3",
                       "yuk 4"
                     }),
                  });


/*
 * Function name: create_monster
 * Description:   creates the guard
 * Arguments:     none
 * Returns:       none
 */

create_monster()
{
    seteuid(getuid());

    /* descritpion */

    set_race_name("doctor");

    set_adj(({"clean","educated"}));

    set_long("This is one of the doctor of the Gelan hospital");

    set_gender(G_MALE);

    set_alignment(1000);

    /* stats and skills */

    default_config_npc(10);    			/* make it intelligent, but */
                                                /* not strong */

    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);

    set_skill(SS_SPELLCRAFT, 	 90);           /* it's a magical guard */

    set_hp(this_object()->query_max_hp());	/* starts with full strength */
    set_mana(this_object()->query_max_mana());

    /* properties */

    add_prop(OBJ_I_WEIGHT, 55000);
    add_prop(OBJ_I_VOLUME, 25000);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 0);
    add_prop(LIVE_I_SEE_INVIS, 0);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    /* armour */

    /* actions */
    set_act_time(50);
    add_act("smile");
    add_act("bow");
    add_act("twiddle");
  
    set_cchat_time(50);
    add_cchat("Hi there");
    seteuid(getuid());

}

/*
 * Function name: help_other
 * Description:   react on help call from master guard (shadow original
                  function)
 * Arguments:     the nearest meeting room to the attacked guard,
                  the room the guard is attacked in,
                  the object pointer to the attacker
 * Returns:       none
 */

void
help_other(int meeting, string room, object attacker)
{

    command("say Well, someone just attacked one of our guards.");
    command("say You'd better be carefull in the town.");

}


/* shouldn't go anywhere when an enemy leaves */
void
notify_enemy_gone(object attacked)
{
}


int
special_attack(object enemy)
{
 
}

/*
 * Function name: heal_me
 * Description:   the player wants to be healed
 * Arguments:     none
 * Returns:       none
 */

int
heal_me()
{
  object contract;                 /* the contract for the player */
  object player;                   /* the player starting this command */
  int hp;                          /* the hp of the player */
  int maxHp;                       /* the max hp of the player */
  int maxHeal;                     /* the maximum number of hps to heal */
  int hpAdj;                       /* the adjustment to the hp */

  float fail;                      /* the chance to fail */
  int cost;                        /* the player will have to pay this many coppers */
  float risk;                      /* this is the estimated chance for success
                                    * bad docs can make mistakes here :-) */
  int playerRisk;                  /* the risk the player is telled */
  int scratch;
  player = this_player();

  hp = player->query_hp();
  maxHp = player->query_max_hp();
  maxHeal = maxHp - hp;

  /* let's log the name */

  log_file(LOG, player->query_name() + ": ");

  /* let's first give the diagnose */
  
  scratch = hp * sizeof(diagnose) / maxHp -1;

  if(scratch < 0)
    scratch = 0;

  write(diagnose[scratch]);

  /* now we compute the cost for the operation */

  cost = ftoi(itof(maxHeal * costHp) * docQual);

  log_file(LOG, "cost " + cost);

  /* first we determine the chance of failure */
  fail = 1.0 - itof(hp) / itof(maxHp);

  write("fail: " + ftoi(fail * 100.0) + "%\n");

  log_file(LOG, ", fail " + ftoi(fail * 100.0) + "%");

  /* now let's se how big the risks are */

  risk = fail / (10.0 * docQual);

  write("risk: " + ftoi(risk * 100.0) + "%\n");

  log_file(LOG, ", risk " + ftoi(risk * 100.0) + "%");

  /* now we change that risk according to the knowledge of the doc */

  playerRisk = ftoi((risk + rnd() * (1.0 - docQual) - (1.0 - docQual) / 2.0) * itof(sizeof(riskDesc) - 1));

  if(playerRisk < 0)
    playerRisk = 0;
  else
    if(playerRisk == 1 && risk != 0)
       playerRisk = 1;
    else
      if(playerRisk >= sizeof(riskDesc))
        playerRisk = sizeof(riskDesc) - 1;

  /* now tell the player the risk and the cost */

  log_file(LOG, " (" + riskDesc[playerRisk] + ")\n");

  write("\nThe cost for this healing would be " + cost + ".\n");
  write("The risk for failure is " + riskDesc[playerRisk] + ".\n");

  /* now the player has to decide if he wants the treatment or not 
   * we let the player sign a contract, and he has to pay afterwards
   * in the lobby
   */

  command("say If you want me trying to cure you, you have to sign this " +
        "contract, in which you agree to pay the demanded fee.\n" +
        "You also accept, that we take no responsability at all " +
        "for any failures, whatever they are.\n");


  /* Now let's give the contract to the player */

  contract = clone_object(GELAN_OBJECTS + "contract");
  contract->fill(player->query_name(), maxHeal);

  write("The doctor gives you a sheet of paper.\n");
  if(contract->move(player))
  {
    command("say Well, I put it here on the desk, take it if you want.\n");
    command("drop contract");
  }
  
  return 1;

}

void
do_heal(int maxHeal)
{
  object player;
  int hp;
  int maxHp;
  float risk;
  float fail;
  int hpAdj;

  player = this_player();
  hp = player->query_hp();
  maxHp = player->query_max_hp();

  /* we calculate the risk new here, because health of player 
   * could have changed 
   */

  fail = 1.0 - itof(hp) / itof(maxHp);
  risk = fail / (10.0 * docQual);

  /* now we check if the doctor can handle that task */

  if(rnd() >= risk)
    /* ok, we succeeded */
    hpAdj = ftoi(itof(maxHeal) * pow(rnd(), 2.0 * (1.0 - docQual)));
  else
    /* too bad, we fail :-) */
    hpAdj = -random(hp);

  player->heal_hp(hpAdj);
  write("I healed " + hpAdj + "\n");

  log_file(LOG, player->query_name() + ": ");
  log_file(LOG, "healed " + hpAdj + ".\n");

  return;
}

/*
 * Function name: cure_me
 * Description:   the player wants to be cured from poison
 * Arguments:     none
 * Returns:       none
 */

int
cure_me()
{


  return 1;
}

/*
 * Function name: init
 * Description:   add the commands to the player
 * Arguments:     none
 * Returns:       none
 */

void
init()
{
  add_action("heal_me","heal");
  add_action("cure_me","cure");
  ::init();

}

/*
 * Function name: setQual
 * Description:   sets the quality of the doc
 * Arguments:     newQual : integer with the new % value
 * Returns:       none
 */

void
setQual(int newQual)
{
  docQual = itof(newQual) / 100.0;
}


void
enter_inv(object ob, object from)
{
  int maxHeal;

  ::enter_inv(ob, from);

  if((MASTER_OB(ob)) == GELAN_OBJECTS + "contract")
  {
    if(from->query_name() != ob->get_player())
    {
      command("say This treatment is not for you !");
      command("tear contract");
      return;
    }

    if(ob->get_signed() != "signed")
    {
      command("say Sorry, you have to sign the contract first !");
      
      /* Now let's give the contract back to the player */

      write("The doctor gives you a sheet of paper.\n");
      if(ob->move(from))
      {
        command("say Well, I put it here on the desk, take it if you want.\n");
        command("drop contract");
      }
      
      return;
    }

    maxHeal = ob->getMaxHeal();

    ob->remove_object();
    do_heal(maxHeal);
  }
}
