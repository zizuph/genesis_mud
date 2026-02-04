/*  
 *  Core code taken from Jonas.c:

    Dolmoor.c
    Dolmoor the hermit lives within the Elderwood forest.
 
 * 
 *  Tomas  -- June 2000
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>

#define MASTIFF1     "/d/Terel/mountains/elderwood/monster/mastiff1"
#define MASTIFF2     "/d/Terel/mountains/elderwood/monster/mastiff2"

int alarm_id;


// function prototypes
int             come_back();
int             special_attack(object baddie);
void            create_monster();
   // void            dress_me();


/*
  Function:  come_back     
  Purpose:   allows Dolmoor after his enemies are gone.
 */
int
come_back()
{

  object *enemy_list;
  object *room_list;
  object porch;
  int i;

  porch=find_object (MOUNTAIN_DIR+"elderwood/forest/porch.c");

  enemy_list=query_my_enemies();

  room_list=FILTER_LIVE ( all_inventory(porch) );

  for (i=0;i<sizeof(room_list);i++)
    {
      if (member_array(room_list[i], enemy_list))
        { tell_room(MOUNTAIN_DIR+"elderwood/forest/porch.c", "Dolmoor peers suspiciously "+
                    "through a slit in the wall.\n"); 
          return 1;
        }
    }

  move_living("M",MOUNTAIN_DIR + "elderwood/forest/porch.c");
  command ("emote peers suspiciously through a slit in the wall.");
  command("emote unlocks the door and sits down on the porch step " +
          "sighing in relief.");

  if (get_alarm(alarm_id)) remove_alarm(alarm_id);

  alarm_id=0;

  return 1;

}

/*
  Function;      special_attack
  Purpose:       to move Dolmoor to the cabin whenever
                 he is attacked.  starts an alarm that will let him return
*/

int
special_attack(object baddie)
{

    command("shout COME HERE BOYS! FETCH!!");

    FIX_EUID;
    clone_object(MASTIFF1)->move_living("west", ETO, 0, 0);
    clone_object(MASTIFF2)->move_living("south", ETO, 0, 0);
    command("stand");
    command("emote runs for the door which opens before him. " +
       "The door slams shut and you hear several locks being " +
       "thrown from the inside.");
    move_living("M",MOUNTAIN_DIR+"elderwood/forest/cabin.c");
    alarm_id = set_alarm(2.0,600.0,&come_back() );

    return 1;
}


void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("Dolmoor");
    set_living_name("Dolmoor Olas");
    enable_intro();
    add_name("dolmoor");
    add_name("olas");
    add_name("hermit");
    set_race_name("human");
    set_title("Retired Merchant of Last"); 
    set_alignment(1200);
    add_adj( ({"bald", "old"}) );

    default_config_npc(150);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 40);
    set_skill(SS_UNARM_COMBAT, 100);

    set_hp(9999);

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);

    set_chat_time(20);
    add_chat("Elderwood is so peaceful. Moreso, than that so called " +
       "civilized mess south.");
    add_chat("Fishing is good here on the lake. Provided you have the " +
       "right bait.");

    set_act_time(15);
    add_act("emote rubs his chin thoughfully.");
    add_act("grin merrily");
    add_act("sit on stoop");

    add_prop(LIVE_I_QUICKNESS, 80);

 //   dress_me();

 //   trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
}

/*
void
dress_me()
{
    FIX_EUID;
 
    clone_unique(WEP_DIR + "sword",5,WEP_DIR + "curved_sword")->move(TO);
    clone_unique(ARM_DIR + "furrobe",5,ARM_DIR + "furs")->move(TO);
    clone_object(SPELL_DIR + "gl_spells")->move(TO); 
    clone_object(ARM_DIR + "headdress")->move(TO);
    clone_object(ARM_DIR + "boots")->move(TO);
    command("wield all");
    command("wear all");
}

*/


void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
       arr[i]->notify_ob_attacked_me(this_object(), ob);
   ob->add_prop("_dolmoor_attacked",1);
}