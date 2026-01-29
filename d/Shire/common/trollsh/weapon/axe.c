inherit "/std/weapon";
inherit "/d/Immortal/rogon/open/tell";
inherit "/d/Immortal/rogon/open/message";

#include "defs.h"
#include <filter_funs.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/common/include/lib.h"

#define WC_PEN 40
#define WC_HIT 30

create_weapon()
{
    "/d/Immortal/rogon/lib/lib"->load_me();
    set_name("axe");  
    add_name("_balins_axe_");
    add_name("waraxe");
    set_short("flashing waraxe");
    set_pshort("flashing waraxes");
    set_pname("axes");
    set_long("@@long_axe");

    set_adj(({"mithril","balins", "enchanted","flashing"}));
    
    set_default_weapon(WC_HIT, WC_PEN, W_AXE, W_SLASH | W_BLUDGEON, 
	"@@check_str", this_object());
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30, 40) + random(700) + 2000);
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(OBJ_M_NO_BUY, "The axe doesnt seem too happy of being sold!\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON ,1);
    add_prop(MAGIC_AM_MAGIC,
        ({
           20,"enchantment", 
           30, "evil-slaying"
           }));
    add_prop(MAGIC_AM_ID_INFO, ({"The axe seems to give of some sort of light.\n",1,
                                "This dwarven waraxe seems like an unusual axe.\n",15,
                                "This waraxe is made of mithril, it is powerful but doesnt weigh that much.\n",34,
                                "It is slaying evil creatures, because the troll who is wielding it needs it powers "
                                +"to control his troops of orcs and trolls, they fear this axe, giving of light and "
                                +"hitting them hard, evil as they are. see magicfile for more info about why evil slaying.\n",58,
           }));
    
}

int
check_str()
{
   if(TP->query_stat(SS_STR) <= 120)
	return W_BOTH;
   else
  	return W_ANYH;
}

int
query_usable(object who)
{
        return (who->query_race()=="dwarf" ||
                who->query_stat(SS_WIS)>50 ||
                who->query_skill(SS_INT)>70) && (who->query_alignment()>200 &&
                who->query_skill(SS_WEP_AXE)>50);

}

public int
wield(object to)
{
    object wielder = ENV(to);
    string wield_msg;

    if(!wielder) return -1;

    switch(wielded_in_hand)
    {
        case W_BOTH:
            wield_msg = "in both your hands";
            break;
        case W_LEFT:
            wield_msg = "in your left hand";
            break;
        case W_RIGHT:
            wield_msg = "in your right hand";
            break;
    }
    
    if(!query_usable(wielder))
    {
        write(
        "You try to wield the dwarvish axe, but you cut yourself on it!\n");
        say(QCTNAME(TP)+" screams loudly as "+HE_SHE(TP)+" tries to wield the dwarvish waraxe.\n");
        TP->command("drop _balins_axe_");
	write("The axe doesn't like being handled like that!\n");
        return -1;
    }
    if(wielder->query_race_name()=="dwarf")
    {
       write(
           "As you swing the dwarven waraxe trough the air, "+wield_msg+", you realize "
          +"the might of this dwarvish craftswork. It feels light, almost as if you had nothing "
          +"in you hands. It is almost like it is alive, pulsating in your hands!\n");
       say(QCTNAME(TP)+" masterly wields the dwarvish axe.\n"+
         CAP(HE_SHE(TP))+" swings the waraxe trough the air, and "+QTNAME(TP)+" looks mighty and powerful "+
                           "with it.\n");
       return 0;
    }
    write(
       "Lightning strikes out of the great waraxe as you wield it "+wield_msg+".\n"+
       "Even though you are not so known with the dwarven fashion of warcraft, you feel  "+
       "that there are great powers within the axe, pulsating trough the blade of the axe.\n");
    say("Lightning flashes from the blade of the waraxe as "+QCTNAME(TP)+" wields it!\n");
    return 0;
}

int
unwield()
{ 
    return 0; 
}

string
long_axe() 
{
  if(query_usable(this_player()))
  return
   "BEHOLD, for thou hast foundest the great waraxe of Balin!\n"
   +"    It has been long lost, ever since he dared entering Khazad-dum where "
   +"he met Durin's bane, the great Balrog of Moria! It might not be as powerful "
   +"as Durin's axe, but you can feel that it holds great powers. It is a light "
   +"waraxe, and it is radiating a yellow light from the axe. The axe is made of "
   +"a mithril alloy called Ithilnaur, a strong metal indeed. The edges of this "
   +"axe is covered with blood and you gather that must be because the trolls have "
   +"been using the axe.\n";
   
 else
   return
   "This is a rather large waraxe, covered with blood on the blade.\n";
}

int
try_hit(object enemy)
{
    object tp = query_wielded();
    
    if(enemy->query_alignment()>0)
        tp->catch_msg("The waraxe does not seem happy trying to hit "+QCTNAME(enemy)+"!!\n");
        
    if(enemy->query_alignment()>250)
    {
        tp->catch_msg(
            "A sudden flash of light hits your hands as you try to dishonour Balin!\n");
            query_wielded()->heal_hp(-random(enemy->query_alignment()/6));
            tellem(tp, enemy, "$N $drop the waraxe as the lightning hits $o!\n");
            query_wielded()->command("drop _balins_axe_");
            
    }
    
   return enemy->query_alignment()<=0;
}


did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object tp;
    string how, good, into, vrb, where,matter;
    int extra_dam = 0;
    
    tp = query_wielded();
    if(!query_usable(tp))
       return 0;
       
    if(enemy->query_alignment()<0)
       extra_dam += -(random(enemy->query_alignment())/2);
    if(enemy->query_race_name()=="troll")
       extra_dam += random(0.9*dam);
    if(enemy->query_race_name()=="dragon")
       extra_dam += random(0.9*dam);   
    extra_dam = random(extra_dam);
    if(dam<=0)
       extra_dam = 0;
    /*if (extra_dam > 150) extra_dam = 150;*/
    /*if (extra_dam = 150) extra_dam = random(150);*/
    /*extra_dam = random(dam*extra_dam/400);
    extra_dam = MAX(extra_dam, 600);*/
    
    if(extra_dam>100)
       tellem(tp,enemy,
             "$N's waraxe flashes as lightning embraces $n's $hand!!!\n");
    else if(extra_dam>80)
       tellem(tp,enemy,
             "Lightning crackles down the blade of $n's waraxe!!\n");
    else if(extra_dam>40)
       tellem(tp,enemy,
             "$N's waraxe glows with a bright white light!\n");
    else if(extra_dam>20)
       tellem(tp,enemy,
             "$N's waraxe does not seem happy.\n");
    
    /*extra_dam = dam*extra_dam/300;*/
    
    enemy->heal_hp(-extra_dam);
    
    phit  += extra_dam/MAX_HP(enemy);
    phurt += extra_dam*100/MAX_HP(enemy);
    
    if (HP(enemy)<= 0)
    {
        if (hdesc=="body")
            matter  = "guts";
        else
            matter = "blood";  
        
        tp->catch_msg(
          "Your mighty waraxe cackles as you smash "+QTNAME(enemy)+" hard upon "+HIS_HER(enemy)+" "+hdesc+"!!\n"+
          QCTNAME(enemy)+" staggers as "+matter+" pour from "+HIS_HER(enemy)+" body!!\n"+
          QCTNAME(enemy)+" looks at you with empty eyes!\n"+
          QCTNAME(enemy)+" screams loudly in pain!!\n"+
          QCTNAME(enemy)+" falls to the ground in a puddle of meat, not easily recognisable as a corpse!\n");
          
      enemy->catch_msg(
          QCTNAME(tp)+" leaps "+HIS_HER(enemy)+" mighty war axe deep into your "+hdesc+"!!\n"+
          "You stagger as you watch your "+matter+" leave your body!\n"+
          "Suddenly you can see nothing, it all gets black!\n"+
          "Your scream loudly in pain!.\n"+
          "Looking at the blood-covered floor, you feel your life fade away ...\n");
      
      tell_room(ENV(tp),
          QCTNAME(tp)+" smashes "+QCTNAME(enemy)+" powerfully onto "+HIS_HER(enemy)+" "+hdesc+"!\n"+
          QCTNAME(enemy)+" staggers as "+matter+" pours out of the cut!\n"+
          QCTNAME(enemy)+" looks at "+QCTNAME(tp)+" with empty eyes.\n"+
          QCTNAME(enemy)+" screams loudly in pain!!\n"+
          QCTNAME(enemy)+" falls to the ground in a puddle of meat, not easily recognisable as a corpse!\n",
          ({ tp, enemy}));
          
      enemy->do_die(tp);
      return 1;
    }
        
    if (dt == W_SLASH)
       {
          how  = ({ "slash", "cut", "hit", "touch" })[random(4)];
          into = "into";
          vrb  = ({ "yawns", "moans", "penetrates", "sings" })[random(4)];
       }
       else 
       {
          how  = ({ "crush", "smash", "strike" })[random(3)];
          into = "upon";
          vrb  =({ "shatters", "hews", "swings" })[random(3)];
       }
       produce_message(tp, enemy, phurt, ({
          ({
             "$N $aim for #n's &body with the waraxe, but $misses.",
             "$N's waraxe leaps towards #n &body, but $misses by a few inches!",
             "$N looked like $s had a dangerous stroke, but missed!!"
          })[random(3)],
          "$N's waraxe strikes #n's &body with a forceful strike!. Extra damage: "+extra_dam+"",
          "$N grazes #n's &body with the waraxe. Extra damage: "+extra_dam+"",
          "$N $&perform a powerful stroke which &swings &into #n's &body!! Extra damage: "+extra_dam+"",
          "$N $&slash the dwarven waraxe &into #n's &body. Extra_dam: "+extra_dam+".",
          "$N $&slash &into #n's &body with $p waraxe! Extra damage: "+extra_dam+".",
          "In a fiercefull attack, $n's dwarven waraxe &swings &into #n's &body!!! Extra damage: "+extra_dam+"",
          "$N's devastating &slash &swings deeply into #n's &body!! Extra damage: "+extra_dam+"",
          "$N $grin as $p mighty waraxe swings &into #n's &body.\n Extra damage: "+extra_dam+"", 
          "Guts flows as $n's axe &swings &into #n's &body!! Extra damage: "+extra_dam+"",
          "$N's waraxe massacres #n in a forceful strike."
          +"It leaps deep into {the poor &troll's;your;"
          +"the poor &troll's} &body with a bone-breaking sound!!",
           "$N's waraxe sings in joy as it &swings &into #n's &body in a breathtaking stroke!"
       }),
       
        ([
          "&swings" : vrb,
          "&into"   : into,
          "&body"   : hdesc,
          "&slash"  : how,
          "&troll"  :enemy->query_race_name()
       ]));
       return 1;
}
/*
string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
*/
init()
{
    ::init();
    if(!query_usable(TP))
    return;
    add_action("do_show", "show");
    add_action("do_love", "love");
    add_action("do_kiss", "kiss");
}

int
do_show(string arg)
{
    if (!id(arg))
        return 0;
    action("$N $swing $p mighty waraxe trough the air!\n"+
    "{You feel the powers of Balin flash trough the blade of yourmighty waraxe. ; "+
    ";You are overcome by the sight of this great waraxe!}\n");
    return 1;
}

int
do_love(string arg)
{
    if (!id(arg))
        return 0;
    action("$N $kiss the head of the waraxe with tears in $n's eyes!\n");
    return 1;
}

int
do_kiss(string arg)
{
    if (!id(arg))
       return 0;
    action("$N $kiss $p mighty waraxe on the shaft and $scream loudly!!!\n");
    return 1;
}
