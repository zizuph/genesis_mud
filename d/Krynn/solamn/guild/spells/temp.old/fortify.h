/*
   NAME:       Fortify
   COST:       30 Mana (10 fail)
   TAX:        ? * 1.5 (no material component) = 
   CLASS:      
   AoE:	       caster only
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      SS_WIS, SS_INT
   DESC:       Success clones a magical shield to Knight
   FAIL:       
   REQUIRED:   Knight of Sword or Rose, medal of Paladine,
*/
#include <cmdparse.h> "There is no prestige to be won by suicide.\n"
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"

#define FORT_MIN  50
// Mana was originally 60
#define FORT_MANA 30
#define DEBUG      0


mixed
fortify()
{
    int mana, level;
    object shieldobj, ob, room;

#if DEBUG
    is_a_wiz = 0;
#endif
    
    room = environment(this_player());
    
    if (!(ob = P("pal_med", TP)))
      return "You have no medal, you should seek guidance.\n";
    
    if (present("shieldobj", TP))
      return "This prayer is already in operation!\n";
    
    if (RNMAGIC(room))
      return "Some force around you distracts you from your prayers.\n";

    if (!(is_a_wiz)) && (TP->query_knight_level() < 4)
        return "Only Sword and Rose Knights may attempt this spell!\n";
    
    if (random(TP->query_stat(SS_WIS)) < random(30))
      return "You begin to pray but lose concentration.\n";

    if ((!(is_a_wiz)) && (random(TP->query_skill(SS_ELEMENT_LIFE) + 
       TP->query_skill(SS_FORM_DIVINATION) + TP->query_skill(SS_SPELLCRAFT) + 
       TP->query_skill(SS_AWARENESS)) / 2 < random(FORT_MIN))
       {
#if DEBUG
           write("SPELL FAILURE: Skill average too low.");
#endif
           write("You clasp the medal of Paladine in your hand, focussing"+
               " your mind.\n");
           tell_room(E(TP), "\n" + QCTNAME(TP) +
               " clasps a platinum medal in " + TP->query_possessive() + " fist " +
               " and mumbles a prayer under " + TP->query_possessive() + " breath.\n", TP);
           write("You pray to Paladine for his protection.\n");
           write("Despite your best efforts, your prayer is unheard.\n");
           TP->add_mana(-(FORT_MANA) / 5);
           return 1;
       }
      
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);

#if DEBUG
    write("SPELL SUCCESS: Skills average is high enough.\n");
#endif
    TP->add_mana(-(FORT_MANA));
    write("You clasp the medal of Paladine in your hand, focussing "+
        " your mind.\n");
    write("You pray for Paladine's protection.\n");
    tell_room(E(TP), "\n" + QCTNAME(TP) + 
        " clasps a platinum medal in " + TP->query_possessive() + " fist " +
        " and mumbles a prayer under " + TP->query_possessive() + " breath.\n", TP);
       
    seteuid(getuid(TO));
    
    level = TP->query_knight_level();
    shieldobj = clone_object(OBJ + "shieldobj");
    shieldobj->set_duration(random(TP->query_stat(SS_INT) *2) + (level * 20));
                                                           
    shieldobj->move(TO);
    TP->wear_arm(shieldobj);
    write("You feel the power of Paladine's protection shielding you.");
    return 1;
}


