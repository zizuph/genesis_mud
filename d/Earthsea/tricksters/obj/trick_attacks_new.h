#include <wa_types.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>

#include "../defs.h"

#define DEBUG(x) find_player("ged")->catch_msg(x)

int stop=0;

void stop()
{
 write("Stoped strangle.\n");
 stop=1;
}

void release()
{
 write("Released strangle.\n");
 stop=0;
}

mapping query_trick_attacks()
{
 return (["strangle":"strangle"]);
}


int is_living(object ob)
{
 if(!living(ob) || ob==TP) return 0;
 return 1;
}

int stranglable(object ob)
{
 string *locs;
 int i,body=0,head=0,neck=0;

 locs=map(ob->query_combat_object()->query_hitloc_id(),
   &(ob->query_combat_object())->cb_hitloc_desc());
 for(i=0;i<sizeof(locs);i++)
  {
   if(sizeof(pcre_search(locs[i],"body"))) body=1;
   if(sizeof(pcre_search(locs[i],"head"))) head=1;
   if(sizeof(pcre_search(locs[i],"neck"))) neck=1;
  }

 return ((body && head) || neck);
}

int can_see_strangle(object tr, object pl)
{
 int skill,lvl;

 if(pl->query_option(OPT_BLOOD)) return 0;
 if(pl->query_wiz_level()) return 2;

 skill=pl->query_skill(SS_AWARENESS)/10+pl->query_stat(SS_WIS)/12+
   random(pl->query_stat(SS_INT)/15);
 lvl=tr->query_trickster_level();

 if(skill<lvl*7/10) return 0;
 if(skill<lvl) return 1;
 return 2;
}

void show_onlookers(object *onlooker,object tr,object enm)
{
 int i;

 for(i=0;i<sizeof(onlooker);i++)
  {
   switch(can_see_strangle(tr,onlooker[i]))
    {
     case 1:
       onlooker[i]->catch_msg("You barely notice "+
         QTPN(tr,onlooker[i])+" swing towards "+QTN(enm,onlooker[i])+
         ", but you are not sure what "+PRO(tr)+" has done.\n");
       break;
     case 2:
       onlooker[i]->catch_msg(QTN(tr,onlooker[i])+" swings something "+
         "resembling scarf towards "+QTPN(enm,onlooker[i])+" neck.\n");
       break;
    }
  }
}

string *get_hit_desc(object tr,object enm,int hitres)
{
 mixed *res;

 if(hitres>=0) res=
  ({QTN(enm,tr)+" manages to break free and seems almost unaffected "+
    "by your attack.\n","You manage to break free and seem unaffected "+
    "by "+POS(tr)+" attack.\n",0});
 if(hitres>5) res=
  ({QTN(enm,tr)+" manages to break free , but your rumel leaves a "+
    "small bruise on "+POS(enm)+" neck.\n","You manage to break free "+
    ", but "+POS(tr)+"attack leaves a small bruise on your neck.\n",0});
 if(hitres>10) res=
  ({QTN(enm,tr)+" manages to break free , but you hear "+POS(enm)+
    " neck cracks.\n","You manage to break free , but you hear your "+
    "neck cracks.\n",60});
 if(hitres>20) res=
  ({QTN(enm,tr)+" manages to break free , but looks very dizzled "+
    "and hurt by your attack.\n","You manage to break free , but "+
    "you are stuned by immense pain "+POS(tr)+" blow caused.\n",120});
 if(hitres>35) res=
  ({QTN(enm,tr)+" barely manages to break free and shrieks loudly "+
    "as your rumel leaves a deep nasty bruise on "+POS(enm)+" neck.\n",
    "You barely manage to break free and shriek loudly as "+POS(tr)+
    " attack leaves a deep nasty bruise on your neck.\n",180});
 if(hitres>55) res=
  ({QTN(enm,tr)+" screams in agony , as you almost break "+POS(enm)+
    " neck.\n","You scream in agony , as "+POS(tr)+" blow almost "+
    "breaks your neck.\n",300});

 return res;
}


void remove_recover(object tr)
{
 tr->catch_msg("You are ready to break necks again.\n");
 tr->remove_prop("_trick_i_attack_recover");
}

void set_recover(object tr)
{
 tr->remove_prop("_trick_i_attack_prep");
 tr->add_prop("_trick_i_attack_recover",1);
 set_alarm(RECOVER_TIME,0.0,&remove_recover(tr));
}

void exec_attack(object tr)
{
 int dam,pen,i;
 mixed hitres;
 mixed *desc;
 object block;
 object *onlooker,enm;

 tr->remove_prop("_trick_i_attack_prep");
 enm=tr->query_prop("_trick_i_strangle_target");
 if(!objectp(enm)) enm=tr->query_enemy();

 if(!objectp(enm))
  {
   tr->catch_msg("Your enemy is dead.\n");
   return;
  }

 if(ENV(tr)!=ENV(enm))
  {
   tr->catch_msg(QTN(enm,tr)+" has escaped your attack.\n");
   return;
  }

 if(tr->query_prop(LIVE_I_ATTACK_DELAY))
  {
   tr->catch_msg("You are too stuned to attack.\n");
   return ;
  }

 onlooker=FILTER_PLAYERS(ENV(tr)->subinventory())-({ tr });
 show_onlookers(onlooker,tr,enm);

 if(2*STAT(tr,SS_DEX)+2*STAT(tr,SS_DIS)+STAT(tr,SS_INT)/10<=
    STAT(enm,SS_DEX)+STAT(enm,SS_DIS)+STAT(enm,SS_INT)/15)
  {
   tr->catch_msg("You swing your rumel towards "+
     QtN(enm,tr)+" , but "+PRO(enm)+" aviods it , making "+
     "you lose your balance.\n");
   enm->catch_msg(QTN(tr,enm)+" swings "+POS(tr)+
     " rumel towards you , but you manage to avoid the swing.\n");
   set_recover(tr);
  }
 else
  {
   pen=STAT(tr,SS_STR)/6+STAT(tr,SS_DEX)*2/13+
     random(STAT(tr,SS_WIS)/8);
   dam=F_PENMOD(pen,SKILL(tr,SS_STRANGLE));
   hitres=enm->hit_me(dam,W_BLUDGEON,tr,-1);
   desc=get_hit_desc(tr,enm,hitres[0]);
   tr->catch_msg("You swing your rumel around "+
     QtPN(enm,tr)+" neck and pull with all your strength.\n");
   enm->catch_msg(QTN(tr,enm)+" swings "+POS(tr)+" rumel around "+
     "your neck and tries to strangle you!\n");

   if(enm->query_hp()<=0)
    {
     tr->add_prop("_trick_i_killed_with_rumel",1);
     tr->catch_msg("Your powerfull swing with rumel breaks "+
       QtPN(enm,tr)+" neck!\n");
     enm->catch_msg(QTPN(tr,enm)+" powerfull swing breaks your neck!\n");
     enm->do_die(tr);
     set_recover(tr);
     return;
    }
   
   tr->catch_msg(desc[0]);
   enm->catch_msg(desc[1]);
  }

 set_recover(tr);
 if(desc[2])
  {
   block=present("_trick_block_say_object_",enm);
   if(!block) 
    {
     setuid();
     seteuid(getuid());
     block=clone_object(TRICKSTERS+"obj/block_say_obj");
     block->move(enm);
     block->add_duration(itof(desc[2]));
     block->start_timer();
    }
   else block->add_duration(itof(desc[2]));
  }
} 

void prepare_attack(object tr)
{
 object enm=tr->query_enemy();

 write("You prepare you rumel and start searching for a way to get "+
   "to "+QtPN(enm,TP)+" neck.\n");
 TP->add_prop("_trick_i_attack_prep",1);
 TP->add_prop("_trick_i_strangle_target",enm);
 set_alarm(PREP_TIME,0.0,&exec_attack(tr));
}

int strangle(string who)
{
 object enm,rumel,*obj;

 NF("You already preparing to strangle.\n");
 if(TP->query_prop("_trick_i_attack_prep")) return 0;

 NF("You are not ready to strangle yet.\n");
 if(TP->query_prop("_trick_i_attack_recover")) return 0;

 NF("Strangle is currently unavailable due to maintenance "+
    "activity. It will be back soon though!\n");
 if(stop) return 0;

 enm=TP->query_enemy();
 rumel=present(RUMEL_DESC,TP);

 NF("You cannot do that without rumel.\n");
 if(!rumel) return 0;

 NF("You cannot strangle with your rumel worn!\n");
 if(rumel->query_worn()) return 0;

 if(who)
  {
   obj=CMDPARSE_ONE_ITEM(who,"is_living","is_living");

   NF("Strangle who?\n");
   if(!sizeof(obj)) return 0;

   NF("Uhm? Strangle them all??\n");
   if(sizeof(obj)>1) return 0;

   enm=obj[0];

   NF("But you can't see your target!\n");
   if(!CAN_SEE_IN_ROOM(TP)) return 0;
  }

 NF("But you are not fighting anyone!\n");
 if(!objectp(enm)) return 0;

 NF("You cannot see the target here.\n");
 if(ENV(TP)!=ENV(enm)) return 0;

 
 NF("You cannot strangle "+OBJ(enm)+", since "+PRO(enm)+
   " has no neck.\n");
 if(!stranglable(enm))return 0;

 if(ENV(enm)->query_prop(ROOM_M_NO_ATTACK))
  {
   NF("You swing your rumel towards "+QtN(enm,TP)+" but "+
     "peacefull charm in the air stops you.\n");
   enm->catch_msg(QTN(TP,enm)+" makes some move towards you , but "+
     "stops charmed by the peace in the air.\n");
   return 0;
  }

 if(enm->query_prop(OBJ_M_NO_ATTACK))
  {
   NF("You swing your rumel towards "+QtN(enm,TP)+" but "+
     POS(enm)+" peacefull appearance stops you.\n");
   enm->catch_msg(QTN(TP,enm)+" makes some move towards you , but "+
     "stops charmed by your peacefull appearance.\n");
   return 0;
  }

 if(!F_DARE_ATTACK(TP,enm))
  {
   NF("You start the move towards "+QtN(enm,TP)+
     " but suddenly realize that you don't dare to attack.\n");
   enm->catch_msg(QTN(TP,enm)+" reaches for something with "+POS(TP)+
     " his muscles tence , but suddenly looks with fear at you.\n");
   return 0;
  }

 NF("You are too stuned to attack.\n");
 if(TP->query_prop(LIVE_I_ATTACK_DELAY)) return 0;

 if(!TP->query_npc() && TP->query_met(enm) &&
   TP->query_prop(LIVE_O_LAST_KILL)!=enm &&
   member_array(enm, TP->query_enemy(-1))==-1)
  {
   NF("Strangle "+QtN(enm,TP)+"?\nPlease confirm by "+
     "trying again.\n");
   TP->add_prop(LIVE_O_LAST_KILL,enm);
   return 0;
  }

 TP->attack_object(enm);
 prepare_attack(TP);
 return 1;
}

