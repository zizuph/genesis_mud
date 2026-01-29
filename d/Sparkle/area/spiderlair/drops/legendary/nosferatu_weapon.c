/*
 *  /d/Sparkle/area/spiderlair/drops/legendary/nosferatu_weapon.c
 *
 *  Possessed blood-red <blade/glaive/cleaver/warhammer>
 *
 *  Nerull,  27/2-09.
 * 
 *  This is a weapon, by random chance either becomes a club,
 *  sword, axe or polearm. All weapons are twohanded. The weapon
 *  never dulls, but it doesnt save through armageddon either.
 *  The weapon drains hp and heals the wielder some.
 *
 */ 
 
inherit "/std/weapon";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <std.h>
#include <options.h>
#include <filter_funs.h>
#include "../../defs.h"


#define LOG(x,y) write_file(SPIDER_DIR+"logs/" +x, extract(ctime(time()),\
                 4, 15) +" "+ y )                           



// The creation of the weapon and its type.
public void
create_weapon()
{
	
    set_wt(random(4));

    if (this_object()->query_wt() == 0)
    {	
       set_adj("possessed");
       add_adj("blood-red");
       set_name("greatsword");
       add_name("sword");
       
       set_wt(W_SWORD);
       set_dt(W_SLASH);
      
       set_short("possessed blood-red greatsword");
       set_long("@@std_long");
    }
    
    if (this_object()->query_wt() == 1)
    {	
       set_adj("possessed");
       add_adj("blood-red");
       set_name("glaive");
       add_name("polearm");
       add_name("warglaive");
       
       set_wt(W_POLEARM);
       set_dt(W_IMPALE);
       
       set_short("possessed blood-red warglaive");
        set_long("@@std_long");
    }
    
    if (this_object()->query_wt() == 2)
    {	
       set_adj("possessed");
       add_adj("blood-red");
       set_name("cleaver");
       add_name("axe");
       
       set_wt(W_AXE);
       set_dt(W_SLASH);
       
       set_short("possessed blood-red cleaver");
       set_long("@@std_long");
    }
            
    if (this_object()->query_wt() == 3)
    {	
       set_adj("possessed");
       add_adj("blood-red");
       set_name("warhammer");
       add_name("club");
       
       set_wt(W_CLUB);
       set_dt(W_BLUDGEON);
       
       set_short("possessed blood-red warhammer");
       set_long("@@std_long");
    }
    
    set_hit(50 + random(10));
    set_pen(55 + random(10));

    set_hands(W_BOTH);
    set_wf(this_object());

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen())+40000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 10000); /* 10 kilos. */
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "This weapon is possessed by a demon.\n", 5,
    "This weapon will hurt the enemy and heal " +
    "the wielder by the powers of the demon " +
    "trapped within.\n", 50}));
                                 
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "This is an awesome random weapontype " +
    "wielded by the giant skeleton in Sparkle, outside dragon's " +
    "lair. It drains hp from the enemy and gives a portion of " +
    "that back to the wielder. This weapon is obtainable only " +
    "by killing the guardian that have it. The weapon never " +
    "dulls, but it never saves over armageddon either. There " +
    "is a 1/4th chance per guardianspawn for a spesific weapontype" +
    "<sword/club/axe/polearm> to spawn.\n");
    
    set_likely_dull(0);
    set_likely_break(0);
   
}


// The longdescriptions of the different weapontypes.
string
std_long()
{
	
	  if (query_wt() == 0)
	 	{	 
      return("Looking at this massive greatsword of War renders you " +
      "speechless; Never before have you seen such a wicked-looking " +
      "and outright scary weapon. The hilt consists of a massive " +
      "shard of red-painted bone worked to provide supernaturally " +
      "good grip, although it seems colder than death as you touch " +
      "it. The pommel is reinforced with a rust-coloured metal of some "+
      "sort, and the chilling cold of the hilt seems to emanate from " +
      "this. The crosspiece resembles a horned demon, its horns " +
      "sticking out on both sides of the blade. The massive " +
      "double-edged blade is blood-red with glowing, crimson runes " +
      "flowing along it like veins and razor-sharp hook-like teeth " +
      "sprouting forth along its length.\n");
    }
    
    if (query_wt() == 1)
	 	{	 
      return("Looking at this massive glaive of War renders you " +
      "speechless; Never before have you seen such a wicked-looking " +
      "and outright scary weapon. The hilt consists of a massive " +
      "shard of red-painted bone worked to provide supernaturally " +
      "good grip, although it seems colder than death as you touch " +
      "it. The grip is reinforced with a rust-coloured metal of some " +
      "sort. The massive long wicked blade at the end is blood-red " +
      "with glowing, crimson runes flowing along it like veins and " +
      "razor-sharp hook-like teeth sprouting forth along its whole " +
      "length.\n");
    }
    
    if (query_wt() == 2)
	 	{	 
      return("Looking at this massive cleaver of War renders you " +
      "speechless; Never before have you seen such a wicked-looking " +
      "and outright scary weapon. The hilt consists of a massive " +
      "shard of red-painted bone worked to provide supernaturally " +
      "good grip, although it seems colder than death as you touch " +
      "it. The pommel is reinforced with a  rust-coloured metal of " +
      "some sort, and the chilling cold of the hilt seems to emanate " +
      "from this. The massive heavy blade is blood-red with glowing, " +
      "crimson runes flowing along it like veins and razor-sharp " +
      "hook-like teeth sprouting forth along its length.\n");
    }
    
    if (query_wt() == 3)
	 	{	 
      return("Looking at this massive hammer of War renders you " +
      "speechless; Never before have you seen such a wicked-looking " +
      "and outright scary weapon. The hilt consists of a massive " +
      "shard of red-painted bone worked to provide supernaturally " +
      "good grip, although it seems colder than death as you touch " +
      "it. The pommel is reinforced with a rust-coloured metal of " +
      "some sort, and the chilling cold of the hilt seems to emanate " +
      "from this. The massive head of the hammer is blood-red with " +
      "glowing, crimson runes flowing along it like veins and " +
      "razor-sharp spike-like teeth sprouting forth all around it.\n");
    }
    
    return("This is a buggy weapon.\n");
       
}


// Cool effect when successfully wielding the weapon, for fancyness.
void
empowerment(object ob)
{
    write("You get a sudden lust for butchering everything!\n");
    say(QCTNAME(TP)+" stares dead ahead with slaughter written all over "+
    TP->query_possessive()+" face.\n");
}


// Unless weapon is picked up after the guardians death,
// the weapon will never be wieldable by any mortal, and
// will blink out of existance if wield is attempted.
mixed
wield(object what)
{

    // Broken.
    if (query_prop(OBJ_I_BROKEN))
        return "It is of no use, the weapon is broken.\n";
        
    // The weapon did not drop normally from the guardian.
    if (!query_prop(MORTAL_CAN_USE_THIS))
    {
    		set_alarm(1.0, 0.0, &remove_object());
    		return "The "+short()+" disappears in a puff of smoke!\n";    		    		
    }
    	
    if (query_wt() == 0)
    {
    	
    	  if(TP->query_skill(SS_WEP_SWORD)<80)
        {
      	     write("The "+short()+" assumes control of your mind for " +
      	     "a short moment.\nA terrible low-pitched voice fills your " +
      	     "mind, saying: 'Un-skilled one, thou art not worthy of my " +
      	     "powers.'\n");
      	     say(QCTNAME(TP)+"'s eyes flash briefly " +
      	     "as "+TP->query_pronoun()+" tries to "+
      	     "wield the "+short()+", but fails.\n");
      	     return "You fail to wield the "+short()+".\n";
      	}
    }
        
    if (query_wt() == 1)
    {
    	
    	  if(TP->query_skill(SS_WEP_POLEARM)<80)
        {
      	     write("The "+short()+" assumes control of your mind for " +
      	     "a short moment.\nA terrible low-pitched voice fills your " +
      	     "mind, saying: 'Un-skilled one, thou art not worthy of my " +
      	     "powers.'\n");
      	     say(QCTNAME(TP)+"'s eyes flash briefly " +
      	     "as "+TP->query_pronoun()+" tries to "+
      	     "wield the "+short()+", but fails.\n");
      	     return "You fail to wield the "+short()+".\n";
      	}
    }
        
    if (query_wt() == 2)
    {
    	
    	  if(TP->query_skill(SS_WEP_AXE)<80)
        {
      	     write("The "+short()+" assumes control of your mind for " +
      	     "a short moment.\nA terrible low-pitched voice fills your "+
      	     "mind, saying: 'Un-skilled one, thou art not worthy of my "+
      	     "powers.'\n");
      	     say(QCTNAME(TP)+"'s eyes flash briefly " +
      	     "as "+TP->query_pronoun()+" tries to "+
      	     "wield the "+short()+", but fails.\n");
      	     return "You fail to wield the "+short()+".\n";
      	}
    }
        
    if (query_wt() == 3)
    {
    	
    	  if(TP->query_skill(SS_WEP_CLUB)<80)
        {
      	     write("The "+short()+" assumes control of your mind for " +
      	     "a short moment.\nA terrible low-pitched voice fills your "+
      	     "mind, saying: 'Un-skilled one, thou art not worthy of my "+
      	     "powers.'\n");
      	     say(QCTNAME(TP)+"'s eyes flash briefly " +
      	     "as "+TP->query_pronoun()+" tries to "+
      	     "wield the "+short()+", but fails.\n");
      	     return "You fail to wield the "+short()+".\n";
      	}
    }
      
    write("A powerful jolt sparks through your body as you "+
    "wield the "+short()+", and everything becomes pitch black.\n"+
    "A rumbling voice penetrates your mind, saying: 'Yes, Yes!! " +
    "Thou art truly a worthy weaponmaster! I shall bestow my " +
    "powers upon Thee for a price, the Souls of Thy victims. Go " +
    "now, go and bestow death and grief upon the land! " +
    "Hurry!'\nYou open your eyes again, seeing the world in a " +
     "blood-red colour.\n");
     
    say(QCTNAME(TP)+" suddenly closes "+TP->query_possessive()+" eyes "+
    "and "+TP->query_possessive()+" face twists into an expression of "+
    "extreme pain.\nThen "+TP->query_pronoun()+" straightens " +
    "up, blinks a few times and starts to look around with " +
    "maliciously shining eyes.\n");
      	    
    set_alarm(5.0, 0.0, &empowerment());

    LOG("special_wield", capitalize(this_player()->query_real_name()) +
                " wielded a " + short()+".\n");
   
    return 0;

}


// Standard messages when unwielding the weapon.
mixed
unwield(object what)
{
	
		set_this_player(query_wielded());
    write("You assume full control of yourself as you release " +
    "the "+short()+".\n");
    say(QCTNAME(TP)+"'s eyes shine brightly for a moment then " +
    "dim down to normal again, as "+TP->query_pronoun()+" unwields "+
    TP->query_possessive()+" "+short()+".\n");
         
}

// This weapon never dulls.
int
set_dull(int du)
{
    return 0;
}


// This weapon will never last over armageddon.
public string
query_recover()
{
    return 0;
}


// The weapon special.
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   
    //Messages for the sword.   
    if (query_wt() == 0)
 	  {  
 	  	
        switch(phurt)
        {
            case -1:
	          if (!wielder->query_option(OPT_GAG_MISSES))
	          {
	              wielder->catch_msg("Your "+short()+" slashes the air " +
	              "next to "+QTNAME(enemy)+", a sickly red glow hanging " +
	              "in the shredded air.\n");
	          }
	          
	          if (!enemy->query_option(OPT_GAG_MISSES))
	          {
	              enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" "+
	              "the air next to you, a sickly red glow hanging " +
	              "in the shredded air.\n");
	          }
	          
	          wielder->tell_watcher_miss(QCTNAME(wielder)+"'s "+short()+
	          " slashes the air next to "+QTNAME(enemy)+", a sickly " +
	          "red glow hanging in the shredded air.\n", enemy);
	          break;

            case 0:
	          wielder->catch_msg("Your "+short()+" flashes with hunger " +
	          "as it barely pokes "+QTNAME(enemy)+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" flashes " +
	          "with hunger as it barely pokes you.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "flashes with hunger as it barely " +
	          "pokes "+QTNAME(enemy)+".\n", enemy);
	          break;

            case 1..3:
	          wielder->catch_msg("Your swing misses "+QTNAME(enemy)+", but"+
	          " the "+short()+" directs itself " +
	          "into "+enemy->query_possessive()+" "+hdesc+" on it's own " +
	          "accord, slashing it slightly.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" misses you " +
	          "with "+wielder->query_possessive()+
	          " swing, but the "+short()+" directs itself into your "+hdesc+
	          " on it's own accord, slashing it slightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" misses "+
	          QTNAME(enemy)+" with "+wielder->query_possessive()+" swing, "+
	          "but the "+short()+" directs itself into "+
	          QTNAME(enemy)+"'s "+hdesc+" on it's "+
	          "own accord, slashing it slightly.\n",enemy);
	
	          wielder->catch_msg("Small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin, draining some of it's vitality " +
	          "before returning to the sword. Some of them enter your " +
	          "blood, and you feel stronger!\n");
	          enemy->catch_msg("Small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("Small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 4..6:
	          wielder->catch_msg("Your "+short()+" swings itself " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+", slashing it " +
	          "lightly.\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" swings " +
            "itself into your "+hdesc+", slashing it lightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "swings itself into "+QTNAME(enemy)+"'s "+hdesc+", cutting "+
	          "it lightly.\n",enemy);
	
	          wielder->catch_msg("Small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "vitality before returning to the sword. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("Small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("Small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 7..12:
	          wielder->catch_msg("You quickly dodge to the side and " +
	          "thrust your "+short()+" into "+QTNAME(enemy)+"'s "+
	          hdesc+", easily piercing through the skin.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" quickly dodges to " +
	          "your side and thrusts "+wielder->query_possessive()+" "+
	          short()+" into your "+hdesc+", piercing through your " +
	          "skin.\n");
	          
	          wielder->tell_watcher(QCTNAME(wielder)+" quickly dodges " +
	          "to the side and thrusts "+wielder->query_possessive()+
	          " "+short()+" into "+QTNAME(enemy)+"'s "+hdesc+
	          ", piercing through the skin.\n",enemy);
	
	          wielder->catch_msg("Glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "life-force before returning to the sword. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("Glowing red shadows lick your skin, " +
	          "draining some of it's life-force before darting back to " +
	          "the "+short()+"!\n");
	          wielder->tell_watcher("Glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 13..18:
	          wielder->catch_msg("You heave into "+QTNAME(enemy)+"'s "+
	          hdesc+" with your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" heaves into your "+
	          hdesc+" with "+wielder->query_possessive()+" "+short()+
	          ".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" heaves into " +
	          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("Glowing red shadows flow out of " +
	          "your "+short()+" and into the wound, draining "+
	          QTNAME(enemy)+" of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("Glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\nYou feel signifficantly weaker!\n");
	          wielder->tell_watcher("Glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 19..25:
	          wielder->catch_msg("You run your "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", shredding flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", shredding your flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", shredding flesh.\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows flow out of your "+
	          short()+" and into the wound, draining "+QTNAME(enemy)+
	          " of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\nYou "+
	          "feel signifficantly weaker!\n");
	          wielder->tell_watcher("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 26..35:
	          wielder->catch_msg("You gash "+QTNAME(enemy)+"'s "+
	          hdesc+" with an agressive swing of your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" gashes your "+hdesc+
	          " with an agressive swing of "+wielder->query_possessive()+
	          " "+short()+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" gashes "+
	          QTNAME(enemy)+"'s "+hdesc+" with an agressive swing of "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows shoot forth from "+
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, "+
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows shoot forth from "+
	          QTNAME(wielder)+
	          "'s "+short()+" and enter your wound, draining large " +
	          "quantities of your blood!\n");
	          wielder->tell_watcher("Flashing red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 36..50:
	          wielder->catch_msg("You forcefully ram your "+short()+
	          " into "+QTNAME(enemy)+"'s "+hdesc+", efficiently " +
	          "carving through skin and flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", efficiently carving through your skin and " +
	          "flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", efficiently carving through " +
	          "skin and flesh.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth from " +
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, " +
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, " +
	          "draining large quantities of your "+"blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	  
	          break;
	
            case 51..65:
	          wielder->catch_msg("You slash open a gaping wound in "+
	          QTNAME(enemy)+"'s "+hdesc+" with a demonic slash of " +
	          "your "+short()+", the hooks along the blade greatly " +
	          "intensifying "+QTNAME(enemy)+"'s pain.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" slashes open a " +
	          "gaping wound in your "+hdesc+" with a demonic slash " +
	          "of "+wielder->query_possessive()+" "+short()+", the " +
	          "hooks along the blade causing you unspeakable "+
	          "pain as it rips you apart!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" slashes open a " +
	          "gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with a " +
	          "demonic slash of "+
	          wielder->query_possessive()+" "+short()+", the hooks " +
	          "along the blade greatly intensifying "+QTNAME(enemy)+
	          "'s pain.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth " +
	          "from your "+short()+" and enter "+QTNAME(enemy)+"'s " +
	          "wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, "+
	          "draining large quantities of your blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 66..80:
	          wielder->catch_msg("Demonic strength surges into your " +
	          "arms from the "+short()+", and you swing at "+
	          QTNAME(enemy)+" with full force. The blade tears deeply " +
	          "into "+enemy->query_possessive()+" "+hdesc+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes flare with " +
	          "unholy light as "+wielder->query_pronoun()+" slashes at " +
	          "you with demonic force. "+
	          wielder->query_possessive()+" "+short()+" tears deeply " +
	          "into your "+hdesc+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes flare " +
	          "with unholy light as "+wielder->query_pronoun()+" slashes "+
	          " at "+QTNAME(enemy)+" with demonic force. "+
	          wielder->query_possessive()+" "+short()+" tears deeply " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red shadows " +
	          "flowing out from the "+
	          short()+" enter your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;
	
            case 81..99:
	          wielder->catch_msg("Your "+short()+" pierces through "+
	          QTNAME(enemy)+" like a knife through hot butter as " +
	          "you thrust it into "+enemy->query_possessive()+" "+
	          hdesc+", all the way to the hilt. The hooks on the "+
	          "blade tear loose veins, nerves and splinters "+
	          "of bone along their way!\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+
	          " pierces through you like a knife through hot butter "+
	          "as "+wielder->query_pronoun()+" thrusts it into your "+
	          hdesc+", all the way to the hilt. The hooks on "+
	          "the blade tear loose veins, nerves and splinters of your "+
	          "bone along their way, causing you unbearable pain!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+
	          " pierces through "+QTNAME(enemy)+" like a knife through "+
	          "hot butter as "+QTNAME(wielder)+" thrusts it into "+
	          enemy->query_possessive()+" "+hdesc+", all the way to "+
	          "the hilt. The hooks on the blade tear loose veins, nerves "+
	          "and splinters of bone along their way!\n",enemy);
	          enemy->command("scream");
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red shadows " +
	          "flowing out from the "+short()+" enter your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;

            default:
	          wielder->catch_msg("You lose control of yourself for "+
	          "a moment, and everything turns pitch black!\nYou hear "+
	          "a terrible scream!\nWhen you regain your eyesight "+
	          "you find your "+short()+" plunged into the molested "+
	          "remains of the "+hdesc+" of "+QTNAME(enemy)+", who drops "+
	          "to the ground as a grotesque and pallid corpse.\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes suddenly shine "+
	          "with an unholy, crimson light as he glares at you! For a "+
	          "split second you feel the terrible sensation of cold steel "+
	          "entering your "+hdesc+", then everything turns dark, oh so "+
	          "dark.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes suddenly "+
	          "shine with an unholy, crimson light as "+
	          wielder->query_pronoun()+" glares at "+QTNAME(enemy)+
	          ". "+QCTNAME(enemy)+" suddenly slumps to the ground with "+
	          QTNAME(wielder)+"'s "+short()+" plunged into "+
	          enemy->query_possessive()+" "+hdesc+"!\n", enemy);
	          break;

        }
    
    }
    
    
    
    //Messages for the glaive.   
    if (query_wt() == 1)
 	  {  
 	  	
        switch(phurt)
        {
            case -1:
	          if (!wielder->query_option(OPT_GAG_MISSES))
	          {
	              wielder->catch_msg("Your "+short()+" pokes the air " +
	              "next to "+QTNAME(enemy)+", a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          if (!enemy->query_option(OPT_GAG_MISSES))
	          {
	              enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" "+
	              "pokes the air next to you, a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          wielder->tell_watcher_miss(QCTNAME(wielder)+"'s "+short()+
	          " pokes the air next to "+QTNAME(enemy)+", a sickly " +
	          "red glow hanging in the air.\n", enemy);
	          break;

            case 0:
	          wielder->catch_msg("Your "+short()+" flashes with hunger " +
	          "as it barely touches "+QTNAME(enemy)+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" flashes " +
	          "with hunger as it barely touches you.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "flashes with hunger as it barely " +
	          "touches "+QTNAME(enemy)+".\n", enemy);
	          break;

            case 1..3:
	          wielder->catch_msg("Your thrust misses "+QTNAME(enemy)+
	          ", but the "+short()+" directs itself " +
	          "into "+enemy->query_possessive()+" "+hdesc+
	          " on it's own accord, poking it slightly.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" misses you " +
	          "with "+wielder->query_possessive()+
	          " thrust, but the "+short()+" directs itself into your "+
	          hdesc+" on it's own accord, poking it slightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" misses "+
	          QTNAME(enemy)+" with "+wielder->query_possessive()+
	          " thrust, "+"but the "+short()+" directs itself into "+
	          QTNAME(enemy)+"'s "+hdesc+" on it's "+
	          "own accord, poking it slightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin, draining some of it's vitality " +
	          "before returning to the glaive. Some of them enter your " +
	          "blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " + 
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 4..6:
	          wielder->catch_msg("Your "+short()+" thrusts itself " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+", piercing it " +
	          "lightly.\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" thrusts " + 
            "itself into your "+hdesc+", piercing it lightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "thrusts itself into "+QTNAME(enemy)+"'s "+hdesc+
	          ", piercing it lightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "vitality before returning to the glaive. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 7..12:
	          wielder->catch_msg("You quickly dodge to the side and " +
	          "thrust your "+short()+" into "+QTNAME(enemy)+"'s "+
	          hdesc+", easily piercing through the skin.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" quickly dodges to " +
	          "your side and thrusts "+wielder->query_possessive()+" "+
	          short()+" into your "+hdesc+", piercing through your " +
	          "skin.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" quickly dodges " +
	          "to the side and thrusts "+wielder->query_possessive()+" "+
	          short()+" into "+QTNAME(enemy)+"'s "+hdesc+
	          ", piercing through the skin.\n",enemy);
	
	          wielder->catch_msg("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "life-force before returning to the glaive. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("glowing red shadows lick your skin, " +
	          "draining some of it's life-force before darting back to " +
	          "the "+short()+"!\n");
	          wielder->tell_watcher("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 13..18:
	          wielder->catch_msg("You heave into "+QTNAME(enemy)+"'s "+
	          hdesc+" with your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" heaves into your "+
	          hdesc+" with "+wielder->query_possessive()+" "+short()+
	          ".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" heaves into " +
	          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("glowing red shadows flow out of " +
	          "your "+short()+" and into the wound, draining "+
	          QTNAME(enemy)+" of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\nYou feel signifficantly weaker!\n");
	          wielder->tell_watcher("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 19..25:
	          wielder->catch_msg("You run your "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", piercing flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", piercing your flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", piercing flesh.\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows flow out of your "+
	          short()+" and into the wound, draining "+QTNAME(enemy)+
	          " of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\nYou "+
	          "feel signifficantly weaker!\n");
	          wielder->tell_watcher("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 26..35:
	          wielder->catch_msg("You gash "+QTNAME(enemy)+"'s "+
	          hdesc+" with an agressive thrust of your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" gashes your "+hdesc+
	          " with an agressive thrust of "+wielder->query_possessive()+
	          " "+short()+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" gashes "+
	          QTNAME(enemy)+"'s "+hdesc+" with an agressive thrust of "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows shoot forth from "+
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, "+
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows shoot forth from "+
	          QTNAME(wielder)+
	          "'s "+short()+" and enter your wound, draining large " +
	          "quantities of your blood!\n");
	          wielder->tell_watcher("Flashing red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 36..50:
	          wielder->catch_msg("You forcefully ram your "+short()+
	          " into "+QTNAME(enemy)+"'s "+hdesc+", efficiently " +
	          "carving through skin and flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", efficiently carving through your skin and " +
	          "flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", efficiently carving through " +
	          "skin and flesh.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth from " +
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, " +
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, " +
	          "draining large quantities of your "+"blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	  
	          break;
	
            case 51..65:
	          wielder->catch_msg("You pierce open a gaping wound in "+
	          QTNAME(enemy)+"'s "+hdesc+" with a demonic thrust of " +
	          "your "+short()+", the hooks along the blade greatly " +
	          "intensifying "+QTNAME(enemy)+"'s pain.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" pierces open a " +
	          "gaping wound in your "+hdesc+" with a demonic thrust " +
	          "of "+wielder->query_possessive()+" "+short()+", the " +
	          "hooks along the blade causing you unspeakable "+
	          "pain as it rips you apart!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" pierces open a " +
	          "gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with a " +
	          "demonic thrust of "+
	          wielder->query_possessive()+" "+short()+", the hooks " +
	          "along the blade greatly intensifying "+QTNAME(enemy)+
	          "'s pain.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth " +
	          "from your "+short()+" and enter "+QTNAME(enemy)+"'s " +
	          "wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, "+
	          "draining large quantities of your blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 66..80:
	          wielder->catch_msg("Demonic strength surges into your " +
	          "arms from the "+short()+", and you thrust at "+
	          QTNAME(enemy)+" with full force. The glaive lacerates " +
	          "deeply into "+enemy->query_possessive()+" "+hdesc+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes flare with " +
	          "unholy light as "+wielder->query_pronoun()+" thrusts at " +
	          "you with demonic force. "+
	          wielder->query_possessive()+" "+short()+" lacerates deeply " +
	          "into your "+hdesc+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes flare " +
	          "with unholy light as "+wielder->query_pronoun()+" thrusts "+
	          " at "+QTNAME(enemy)+" with demonic force. "+
	          wielder->query_possessive()+" "+short()+" lacerates deeply " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red shadows " +
	          "flowing out from the "+
	          short()+" enter your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;
	
            case 81..99:
	          wielder->catch_msg("Your "+short()+" pierces through "+
	          QTNAME(enemy)+" like a knife through hot butter as " +
	          "you thrust it into "+enemy->query_possessive()+" "+
	          hdesc+". The hooks on the "+
	          "blade tear loose veins, nerves and splinters "+
	          "of bone along their way!\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+
	          " pierces through you like a knife through hot butter "+
	          "as "+wielder->query_pronoun()+" thrusts it into your "+
	          hdesc+". The hooks on "+
	          "the blade tear loose veins, nerves and splinters of your "+
	          "bone along their way, causing you unbearable pain!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+
	          " pierces through "+QTNAME(enemy)+" like a knife through "+
	          "hot butter as "+QTNAME(wielder)+" thrusts it into "+
	          enemy->query_possessive()+" "+hdesc+". The hooks on " +
	          "the blade tear loose veins, nerves "+
	          "and splinters of bone along their way!\n",enemy);
	          enemy->command("scream");
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red " +
	          "shadows flowing out from the "+short()+" enter " +
	          "your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;

            default:
	          wielder->catch_msg("You lose control of yourself for "+
	          "a moment, and everything turns pitch black!\nYou hear "+
	          "a terrible scream!\nWhen you regain your eyesight "+
	          "you find your "+short()+" plunged into the molested "+
	          "remains of the "+hdesc+" of "+QTNAME(enemy)+", who drops "+
	          "to the ground as a grotesque and pallid corpse.\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes suddenly shine "+
	          "with an unholy, crimson light as he glares at you! For a "+
	          "split second you feel the terrible sensation of imminent " +
	          "death, then everything turns dark, oh so dark.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes suddenly "+
	          "shine with an unholy, crimson light as "+
	          wielder->query_pronoun()+" glares at "+QTNAME(enemy)+
	          ". "+QCTNAME(enemy)+" suddenly slumps to the ground with "+
	          QTNAME(wielder)+"'s "+short()+" plunged into "+
	          enemy->query_possessive()+" "+hdesc+"!\n", enemy);
	          break;

        }
    
    }
    
   
    
    //Messages for the cleaver.   
    if (query_wt() == 2)
 	  {  
 	  	
        switch(phurt)
        {
            case -1:
	          if (!wielder->query_option(OPT_GAG_MISSES))
	          {
	              wielder->catch_msg("Your "+short()+" cut the air " +
	              "next to "+QTNAME(enemy)+", a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          if (!enemy->query_option(OPT_GAG_MISSES))
	          {
	              enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" "+
	              "cuts the air next to you, a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          wielder->tell_watcher_miss(QCTNAME(wielder)+"'s "+short()+
	          " cuts the air next to "+QTNAME(enemy)+", a sickly " +
	          "red glow hanging in the air.\n", enemy);
	          break;

            case 0:
	          wielder->catch_msg("Your "+short()+" flashes with hunger " +
	          "as it barely touches "+QTNAME(enemy)+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" flashes " +
	          "with hunger as it barely touches you.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "flashes with hunger as it barely " +
	          "touches "+QTNAME(enemy)+".\n", enemy);
	          break;

            case 1..3:
	          wielder->catch_msg("Your swing misses "+QTNAME(enemy)+", but"+
	          " the "+short()+" directs itself " +
	          "into "+enemy->query_possessive()+" "+hdesc+" on it's own " +
	          "accord, cutting it slightly.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" misses you " +
	          "with "+wielder->query_possessive()+
	          " swing, but the "+short()+" directs itself into your "+hdesc+
	          " on it's own accord, cutting it slightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" misses "+
	          QTNAME(enemy)+" with "+wielder->query_possessive()+" swing, "+
	          "but the "+short()+" directs itself into "+
	          QTNAME(enemy)+"'s "+hdesc+" on it's "+
	          "own accord, cutting it slightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin, draining some of it's vitality " +
	          "before returning to the cleaver. Some of them enter your " +
	          "blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 4..6:
	          wielder->catch_msg("Your "+short()+" swings itself " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+", hacking it " +
	          "lightly.\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" swings " +
            "itself into your "+hdesc+", hacking it lightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "swings itself into "+QTNAME(enemy)+"'s "+hdesc+", hacking "+
	          "it lightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "vitality before returning to the cleaver. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 7..12:
	          wielder->catch_msg("You quickly dodge to the side and " +
	          "swing your "+short()+" into "+QTNAME(enemy)+"'s "+
	          hdesc+", easily cutting through the skin.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" quickly dodges to " +
	          "your side and swings "+wielder->query_possessive()+" "+
	          short()+" into your "+hdesc+", cutting through your " +
	          "skin.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" quickly dodges " +
	          "to the side and swings "+wielder->query_possessive()+" "+
	          short()+" into "+QTNAME(enemy)+"'s "+hdesc+
	          ", cutting through the skin.\n",enemy);
	
	          wielder->catch_msg("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "life-force before returning to the cleaver. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("glowing red shadows lick your skin, " +
	          "draining some of it's life-force before darting back to " +
	          "the "+short()+"!\n");
	          wielder->tell_watcher("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 13..18:
	          wielder->catch_msg("You heave into "+QTNAME(enemy)+"'s "+
	          hdesc+" with your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" heaves into your "+
	          hdesc+" with "+wielder->query_possessive()+" "+short()+
	          ".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" heaves into " +
	          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("glowing red shadows flow out of " +
	          "your "+short()+" and into the wound, draining "+
	          QTNAME(enemy)+" of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\nYou feel signifficantly weaker!\n");
	          wielder->tell_watcher("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 19..25:
	          wielder->catch_msg("You run your "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", piercing flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", piercing your flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", piercing flesh.\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows flow out of your "+
	          short()+" and into the wound, draining "+QTNAME(enemy)+
	          " of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\nYou "+
	          "feel signifficantly weaker!\n");
	          wielder->tell_watcher("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 26..35:
	          wielder->catch_msg("You gash "+QTNAME(enemy)+"'s "+
	          hdesc+" with an agressive swing of your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" gashes your "+hdesc+
	          " with an agressive swing of "+wielder->query_possessive()+
	          " "+short()+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" gashes "+
	          QTNAME(enemy)+"'s "+hdesc+" with an agressive swing of "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows shoot forth from "+
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, "+
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows shoot forth from "+
	          QTNAME(wielder)+
	          "'s "+short()+" and enter your wound, draining large " +
	          "quantities of your blood!\n");
	          wielder->tell_watcher("Flashing red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 36..50:
	          wielder->catch_msg("You forcefully ram your "+short()+
	          " into "+QTNAME(enemy)+"'s "+hdesc+", efficiently " +
	          "carving through skin and flesh.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", efficiently carving through your skin and " +
	          "flesh.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", efficiently carving through " +
	          "skin and flesh.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth from " +
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, " +
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, " +
	          "draining large quantities of your "+"blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	  
	          break;
	
            case 51..65:
	          wielder->catch_msg("You hack open a gaping wound in "+
	          QTNAME(enemy)+"'s "+hdesc+" with a demonic swing of " +
	          "your "+short()+", the hooks along the heavy blade " +
	          "greatly intensifying "+QTNAME(enemy)+"'s pain.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" hacks open a " +
	          "gaping wound in your "+hdesc+" with a demonic swing " +
	          "of "+wielder->query_possessive()+" "+short()+", the " +
	          "hooks along the heavy blade causing you unspeakable "+
	          "pain as it rips you apart!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" hacks open a " +
	          "gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with a " +
	          "demonic swing of "+
	          wielder->query_possessive()+" "+short()+", the hooks " +
	          "along the blade greatly intensifying "+QTNAME(enemy)+
	          "'s pain.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth " +
	          "from your "+short()+" and enter "+QTNAME(enemy)+"'s " +
	          "wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, "+
	          "draining large quantities of your blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 66..80:
	          wielder->catch_msg("Demonic strength surges into your " +
	          "arms from the "+short()+", and you swing at "+
	          QTNAME(enemy)+" with full force. The cleaver cuts " +
	          "deeply into "+enemy->query_possessive()+" "+hdesc+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes flare with " +
	          "unholy light as "+wielder->query_pronoun()+" swings at " +
	          "you with demonic force. "+
	          wielder->query_possessive()+" "+short()+" cuts deeply " +
	          "into your "+hdesc+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes flare " +
	          "with unholy light as "+wielder->query_pronoun()+" swings "+
	          " at "+QTNAME(enemy)+" with demonic force. "+
	          wielder->query_possessive()+" "+short()+" cuts deeply " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red shadows " +
	          "flowing out from the "+
	          short()+" enter your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;
	
            case 81..99:
	          wielder->catch_msg("Your "+short()+" cuts through "+
	          QTNAME(enemy)+" like a knife through hot butter as " +
	          "you hack it into "+enemy->query_possessive()+" "+
	          hdesc+". The hooks on the "+
	          "heavy blade tear loose veins, nerves and splinters "+
	          "of bone along their way!\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+
	          " cuts through you like a knife through hot butter "+
	          "as "+wielder->query_pronoun()+" hacks it into your "+
	          hdesc+". The hooks on "+
	          "the heavy blade tear loose veins, nerves and splinters " +
	          "of your "+
	          "bone along their way, causing you unbearable pain!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+
	          " cuts through "+QTNAME(enemy)+" like a knife through "+
	          "hot butter as "+QTNAME(wielder)+" hacks it into "+
	          enemy->query_possessive()+" "+hdesc+". The hooks on " +
	          "the heavy blade tear loose veins, nerves "+
	          "and splinters of bone along their way!\n",enemy);
	          enemy->command("scream");
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red " +
	          "shadows flowing out from the "+short()+" enter " +
	          "your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;

            default:
	          wielder->catch_msg("You lose control of yourself for "+
	          "a moment, and everything turns pitch black!\nYou hear "+
	          "a terrible scream!\nWhen you regain your eyesight "+
	          "you find your "+short()+" plunged into the molested "+
	          "remains of the "+hdesc+" of "+QTNAME(enemy)+", who drops "+
	          "to the ground as a grotesque and pallid corpse.\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes suddenly shine "+
	          "with an unholy, crimson light as he glares at you! For a "+
	          "split second you feel the terrible sensation of imminent " +
	          "death, then everything turns dark, oh so dark.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes suddenly "+
	          "shine with an unholy, crimson light as "+
	          wielder->query_pronoun()+" glares at "+QTNAME(enemy)+
	          ". "+QCTNAME(enemy)+" suddenly slumps to the ground with "+
	          QTNAME(wielder)+"'s "+short()+" plunged into "+
	          enemy->query_possessive()+" "+hdesc+"!\n", enemy);
	          break;

        }
    
    }
    
    
    
    //Messages for the warhammer.   
    if (query_wt() == 1)
 	  {  
 	  	
        switch(phurt)
        {
            case -1:
	          if (!wielder->query_option(OPT_GAG_MISSES))
	          {
	              wielder->catch_msg("Your "+short()+" hits the air " +
	              "next to "+QTNAME(enemy)+", a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          if (!enemy->query_option(OPT_GAG_MISSES))
	          {
	              enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" "+
	              "hits the air next to you, a sickly red glow hanging " +
	              "in the air.\n");
	          }
	          
	          wielder->tell_watcher_miss(QCTNAME(wielder)+"'s "+short()+
	          " hits the air next to "+QTNAME(enemy)+", a sickly " +
	          "red glow hanging in the air.\n", enemy);
	          break;

            case 0:
	          wielder->catch_msg("Your "+short()+" flashes with hunger " +
	          "as it barely touches "+QTNAME(enemy)+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" flashes " +
	          "with hunger as it barely touches you.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "flashes with hunger as it barely " +
	          "touches "+QTNAME(enemy)+".\n", enemy);
	          break;

            case 1..3:
	          wielder->catch_msg("Your swing misses "+QTNAME(enemy)+", but"+
	          " the "+short()+" directs itself " +
	          "into "+enemy->query_possessive()+" "+hdesc+" on it's own " +
	          "accord, hitting it slightly.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" misses you " +
	          "with "+wielder->query_possessive()+
	          " swing, but the "+short()+" directs itself into your "+hdesc+
	          " on it's own accord, hitting it slightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" misses "+
	          QTNAME(enemy)+" with "+wielder->query_possessive()+" swing, "+
	          "but the "+short()+" directs itself into "+
	          QTNAME(enemy)+"'s "+hdesc+" on it's "+
	          "own accord, hitting it slightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin, draining some of it's vitality " +
	          "before returning to the hammer. Some of them enter your " +
	          "blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker along "+
	          QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 4..6:
	          wielder->catch_msg("Your "+short()+" swings itself " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+", pounding it " +
	          "lightly.\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+" swings " +
            "itself into your "+hdesc+", pounding it lightly.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+" " +
	          "swings itself into "+QTNAME(enemy)+"'s "+hdesc+", pounding "+
	          "it lightly.\n",enemy);
	
	          wielder->catch_msg("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "vitality before returning to the hammer. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("small red shadows flicker along your " +
	          "skin, draining some of it's vitality before darting back " +
	          "to the "+short()+"!\n");
	          wielder->tell_watcher("small red shadows flicker " +
	          "along "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(5);
	          enemy->heal_hp(-7);
	  
	          break;

            case 7..12:
	          wielder->catch_msg("You quickly dodge to the side and " +
	          "swing your "+short()+" into "+QTNAME(enemy)+"'s "+
	          hdesc+", easily crushing some bones.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" quickly dodges to " +
	          "your side and swings "+wielder->query_possessive()+" "+
	          short()+" into your "+hdesc+", crushing some bones.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" quickly dodges " +
	          "to the side and swings "+wielder->query_possessive()+" "+
	          short()+" into "+QTNAME(enemy)+"'s "+hdesc+
	          ", crushing some bones.\n",enemy);
	
	          wielder->catch_msg("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin, draining some of it's " +
	          "life-force before returning to the hammer. Some of them " +
	          "enter your blood, and you feel stronger!\n");
	          enemy->catch_msg("glowing red shadows lick your skin, " +
	          "draining some of it's life-force before darting back to " +
	          "the "+short()+"!\n");
	          wielder->tell_watcher("glowing red shadows " +
	          "lick "+QTNAME(enemy)+"'s skin.\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 13..18:
	          wielder->catch_msg("You heave into "+QTNAME(enemy)+"'s "+
	          hdesc+" with your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" heaves into your "+
	          hdesc+" with "+wielder->query_possessive()+" "+short()+
	          ".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" heaves into " +
	          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("glowing red shadows flow out of " +
	          "your "+short()+" and into the wound, draining "+
	          QTNAME(enemy)+" of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\nYou feel signifficantly weaker!\n");
	          wielder->tell_watcher("glowing red shadows flow out " +
	          "of "+QTNAME(wielder)+"'s "+short()+" and into the " +
	          "wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 19..25:
	          wielder->catch_msg("You run your "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", smashing bones.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", smashing your bones.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" runs "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", smashing bones.\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows flow out of your "+
	          short()+" and into the wound, draining "+QTNAME(enemy)+
	          " of life-force!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\nYou "+
	          "feel signifficantly weaker!\n");
	          wielder->tell_watcher("Flashing red shadows flow out of "+
	          QTNAME(wielder)+"'s "+short()+" and into the wound!\n",enemy);
	          wielder->heal_hp(10);
	          enemy->heal_hp(-20);
	  
	          break;

            case 26..35:
	          wielder->catch_msg("You smash "+QTNAME(enemy)+"'s "+
	          hdesc+" with an agressive swing of your "+short()+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+" smashes your "+hdesc+
	          " with an agressive swing of "+wielder->query_possessive()+
	          " "+short()+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" smashes "+
	          QTNAME(enemy)+"'s "+hdesc+" with an agressive swing of "+
	          wielder->query_possessive()+" "+short()+".\n",enemy);
	
	          wielder->catch_msg("Flashing red shadows shoot forth from "+
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, "+
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flashing red shadows shoot forth from "+
	          QTNAME(wielder)+
	          "'s "+short()+" and enter your wound, draining large " +
	          "quantities of your blood!\n");
	          wielder->tell_watcher("Flashing red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 36..50:
	          wielder->catch_msg("You forcefully ram your "+short()+
	          " into "+QTNAME(enemy)+"'s "+hdesc+", efficiently " +
	          "plowing through flesh and bones.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into your "+
	          hdesc+", efficiently plowing through your flesh and " +
	          "bones.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" forcefully rams "+
	          wielder->query_possessive()+" "+short()+" into "+
	          QTNAME(enemy)+"'s "+hdesc+", efficiently plowing through " +
	          "flesh and bones.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth from " +
	          "your "+short()+" and enter "+QTNAME(enemy)+"'s wound, " +
	          "draining large quantities of "+enemy->query_possessive()+
	          " blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, " +
	          "draining large quantities of your "+"blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	  
	          break;
	
            case 51..65:
	          wielder->catch_msg("You smash open a gaping wound in "+
	          QTNAME(enemy)+"'s "+hdesc+" with a demonic swing of " +
	          "your "+short()+", the spikes along the hammer greatly " +
	          "intensifying "+QTNAME(enemy)+"'s pain.\n");
	          enemy->catch_msg(QCTNAME(wielder)+" smashes open a " +
	          "gaping wound in your "+hdesc+" with a demonic swing " +
	          "of "+wielder->query_possessive()+" "+short()+", the " +
	          "spikes along the hammer causing you unspeakable "+
	          "pain as it rips you apart!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+" smashes open a " +
	          "gaping wound in "+QTNAME(enemy)+"'s "+hdesc+" with a " +
	          "demonic swing of "+
	          wielder->query_possessive()+" "+short()+", the spikes " +
	          "along the hammer greatly intensifying "+QTNAME(enemy)+
	          "'s pain.\n",enemy);
	
	          wielder->catch_msg("Flaring red shadows shoot forth " +
	          "from your "+short()+" and enter "+QTNAME(enemy)+"'s " +
	          "wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\nYou feel stronger.\n");
	          enemy->catch_msg("Flaring red shadows shoot forth from "+
	          QTNAME(wielder)+"'s "+short()+" and enter your wound, "+
	          "draining large quantities of your blood!\n");
	          wielder->tell_watcher("Flaring red shadows shoot forth " +
	          "from "+QTNAME(wielder)+"'s "+short()+" and enter "+
	          QTNAME(enemy)+"'s wound, draining large quantities of "+
	          enemy->query_possessive()+" blood!\n",enemy);
	          wielder->heal_hp(30);
	          enemy->heal_hp(-40);
	 
	          break;

            case 66..80:
	          wielder->catch_msg("Demonic strength surges into your " +
	          "arms from the "+short()+", and you swing at "+
	          QTNAME(enemy)+" with full force. The hammer plows " +
	          "deeply into "+enemy->query_possessive()+" "+hdesc+".\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes flare with " +
	          "unholy light as "+wielder->query_pronoun()+" swings at " +
	          "you with demonic force. "+
	          wielder->query_possessive()+" "+short()+" plows deeply " +
	          "into your "+hdesc+".\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes flare " +
	          "with unholy light as "+wielder->query_pronoun()+" swings "+
	          " at "+QTNAME(enemy)+" with demonic force. "+
	          wielder->query_possessive()+" "+short()+" plows deeply " +
	          "into "+QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red shadows " +
	          "flowing out from the "+
	          short()+" enter your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;
	
            case 81..99:
	          wielder->catch_msg("Your "+short()+" plows through "+
	          QTNAME(enemy)+" like a knife through hot butter as " +
	          "you swing it into "+enemy->query_possessive()+" "+
	          hdesc+". The spikes on the "+
	          "hammer tear loose veins, nerves and splinters "+
	          "of bone along their way!\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s "+short()+
	          " plows through you like a knife through hot butter "+
	          "as "+wielder->query_pronoun()+" swings it into your "+
	          hdesc+". The spikes on "+
	          "the hammer tear loose veins, nerves and splinters of your "+
	          "bone along their way, causing you unbearable pain!\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s "+short()+
	          " plows through "+QTNAME(enemy)+" like a knife through "+
	          "hot butter as "+QTNAME(wielder)+" swings it into "+
	          enemy->query_possessive()+" "+hdesc+". The spikes on " +
	          "the hammer tear loose veins, nerves "+
	          "and splinters of bone along their way!\n",enemy);
	          enemy->command("scream");
	
	          wielder->catch_msg(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as " +
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n");
	          enemy->catch_msg("You stagger as streaming red " +
	          "shadows flowing out from the "+short()+" enter " +
	          "your wound!\n");
	          wielder->tell_watcher(QCTNAME(enemy)+" staggers and "+
	          enemy->query_possessive()+" eyes begin to flutter as "+
	          "fiery, streaming red shadows flowing from the "+
	          short()+" enter "+enemy->query_possessive()+" wound."+
	          "\n"+QCTNAME(enemy)+" pales considerably.\n",enemy);
	          wielder->heal_hp(40);
	          enemy->heal_hp(-50);
	  
	          break;

            default:
	          wielder->catch_msg("You lose control of yourself for "+
	          "a moment, and everything turns pitch black!\nYou hear "+
	          "a terrible scream!\nWhen you regain your eyesight "+
	          "you find your "+short()+" plunged into the molested "+
	          "remains of the "+hdesc+" of "+QTNAME(enemy)+", who drops "+
	          "to the ground as a grotesque and pallid corpse.\n");
	          enemy->catch_msg(QCTNAME(wielder)+"'s eyes suddenly shine "+
	          "with an unholy, crimson light as he glares at you! For a "+
	          "split second you feel the terrible sensation of imminent " +
	          "death, then everything turns dark, oh so dark.\n");
	          wielder->tell_watcher(QCTNAME(wielder)+"'s eyes suddenly "+
	          "shine with an unholy, crimson light as "+
	          wielder->query_pronoun()+" glares at "+QTNAME(enemy)+
	          ". "+QCTNAME(enemy)+" suddenly slumps to the ground with "+
	          QTNAME(wielder)+"'s "+short()+" plunged into "+
	          enemy->query_possessive()+" "+hdesc+"!\n", enemy);
	          break;

        }
    
    }
    
		return 1;
}










