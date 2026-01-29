/*****************************************************************************
 *                                                                           *
 * Name: Carved quickwood hoopak.                                            *
 *                                                                           *
 * By Elmore, thanks to Belnop the merry kender, for descriptions and ideas! *
 *                                                                           *
 * Type: Polearm / Staff                                                     *
 *                                                                           *
 * Found at: The forest of Mithas. In a black dragons lair near the swampy   *
 *           part of the forest.                                             *
 *                                                                           *
 * Info: This polearm gives any kender a 100% speed bonus and raises the     *
 *       hit and pen to: 47,47. It also uses non-stadard combat messages and *
 *       if examined closely the wielder might find out that it has 4 emotes *
 *       aswell, namely: 'hswing', 'hrun', 'hspin' and 'hfire'.              *
 *       Because of the number of smaller items that can be examined on the  *
 *       weapon. I've made a different Examine procedure. One must study the *
 *       item to get a description, like: 'study second cat' to get the      *
 *       description of the second cat.                                      *
 *                                                                           *
 * Louie Jan 2006 - Added fix to unwield to keep quickness correct.          *
 * Petros Feb 2012 - Changed haste to use an object instead                  *
 * Arman Sep 2020 - Added OBJ_I_AIDS_ACROBATIC benefit when wielded          *
 *                  by kender.                                               *
 * Carnak Mar 2021 - Increased the hit, pen and haste of this item in        *
 *                   accordance with boosts to two-handed weapons.           *
 *****************************************************************************/

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/sys/global/cmdparse.c"
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

#define NORMALPEN 39
#define NORMALHIT 39

#define KENDERPEN 54
#define KENDERHIT 52

#define HASTE_OBJECT "/d/Ansalon/goodlund/nethosak/forest/obj/weapon/hoopak_haste"

int alpeb, alload, alaim, alshoot;
object tstaff;

create_weapon()
{
    setuid();
    seteuid(getuid());
    
    set_name("hoopak");
    add_name("staff");
    set_adj("carved");
    add_adj("quickwood");
    set_short("carved quickwood hoopak");
    set_long("This is a staff, that is for sure, but quite an unusual one. "+
             "It is made from a single piece of wood that seems to shimmer "+
             "with a blue-green tint. You realize this hoopak must have "+
             "been made from a branch of a living quickwood tree. Along "+
             "the entire shaft is an amazing display of creatures, both "+
             "normal but also rare and magical ones, that have been carved "+
             "and decorated with such great skill they almost seem to be "+
             "alive. The shaft ends in the forked top, where one branch "+
             "has been carved as a magnificent golden dragon and the other "+
             "as a beautiful multi-coloured phoenix. A sling made of a "+
             "fiery red leather has been tied between them. The bottom of "+
             "the hoopak is silver clad and comes to a sharp point. Some "+
             "runes have been engraved in the silver. This weapon is so "+
             "detailed that you might want to try and study each amazing "+
             "carving in the weapon. The weapon is so detailed that you "+
             "study each of the creatures more closely.\n");

    set_default_weapon(NORMALHIT, NORMALPEN, W_POLEARM, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(KENDERHIT,KENDERPEN) + 650);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 500);
    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);
    add_prop(OBJ_S_WIZINFO, "This halberd has been carved out of a quickwood, "+
             "making it extremely fast in combat, if wielded by a kender. It has "+
             "couple of emotes aswell. This hoopak also provides maximum " +
             "OBJ_I_AIDS_ACROBATIC benefit when wielded by a kender.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"The weapon is enchanted.\n", 5,
        "This halberd has been made out of quickwood, making it extremely fast "+
        "in combat, if wielded by a kender.\n", 25,
        "It seems to have kender soul within which comes alive when in kenders "+
        "hands.\n", 50}));
    set_wf(TO);
}

mixed
wield(object what)
{
    // There were players who managed to dress up like a kender and wield this weapon
    // To benefit from its magic, without being a true kender. Querying for hobbit as base race
    // will limit this abuse, although not remove it entirely.
    if (TP->query_race_name() == "kender" && TP->query_race() == "hobbit")
    {
        set_hit(KENDERHIT);
        set_pen(KENDERPEN);
        add_prop(OBJ_I_AIDS_ACROBATIC, 100);
        wielder->catch_msg("When you wield the carved quickwood hoopak "+
                           "your head is suddenly filled with the voices "+
                           "of a thousand animals, and you can almost feel "+
                           "the staff move between your hands.\n");
        wielder->tell_watcher(QCTNAME(wielder)+ " wields " +HIS(wielder)+
                              " "+short()+ " in both hands.\nThe animals "+
                              "adorning the hoopak seem to come to life "+
                              "for a short moment. Blinking in surprise, "+
                              "you look again but nothing seems amiss. You "+
                              "wonder if it was a figment of your "+
                              "imagination.\n");

        set_long("This is a staff, that is for sure, but quite an unusual "+
                 "one. It is made from a single piece of wood that seems "+
                 "to shimmer with a blue-green tint. You realize this "+
                 "hoopak must have been made from a branch of a living "+
                 "quickwood tree. Along the entire shaft is an amazing "+
                 "display of creatures, both normal but also rare and "+
                 "magical ones, that have been carved and decorated with "+
                 "such great skill they almost seem to be alive. The "+
                 "shaft ends in the forked top, where one branch has been "+
                 "carved as a magnificent golden dragon and the other as a "+
                 "beautiful multi-coloured phoenix. A sling made of a "+
                 "fiery red leather has been tied between them. The bottom "+
                 "of the hoopak is silver clad and comes to a sharp "+
                 "point. Some runes have been ingraved in the silver. "+
                 "Judging from the shape and adornment, its creator must "+
                 "have been your kin. The weapon is so detailed that you "+
                 "study each of the creatures more closely.\n");
        wielder->update_weapon(TO);
        object haste_object;
        if (haste_object = present("_hoopak_haste_object_", wielder))
        {
            haste_object->remove_object();
        }
        // Clone and move the Hoopak Haste object to the wielder
        haste_object = clone_object(HASTE_OBJECT);
        haste_object->set_hoopak_object(this_object());
        haste_object->move(wielder);
        return 1;
    }
    set_hit(NORMALHIT);
    set_pen(NORMALPEN);
    wielder->catch_msg("You grab around the "+short()+ ".\nYou feel a bit "+
                       "silly trying to wield a kender weapon.\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " wields " +HIS(wielder)+ " "+
                          short()+ ".\n");
    wielder->update_weapon(TO);
    return 1;
}

mixed
unwield(object what)
{
    object haste_object;
    if (haste_object = present("_hoopak_haste_object_", wielder))
    {
        haste_object->remove_object();
    }

    if (wielder->query_race_name() == "kender" && wielder->query_race() == "hobbit")
    {
        set_long("This is a staff, that is for sure, but quite an unusual "+
                 "one. It is made from a single piece of wood that seems "+
                 "to shimmer with a blue-green tint. You realize this "+
                 "hoopak must have been made from a branch of a living "+
                 "quickwood tree. Along the entire shaft is an amazing "+
                 "display of creatures, both normal but also rare and "+
                 "magical ones, that have been carved and decorated with "+
                 "such great skill they almost seem to be alive. The "+
                 "shaft ends in the forked top, where one branch has been "+
                 "carved as a magnificent golden dragon and the other as a "+
                 "beautiful multi-coloured phoenix. A sling made of a "+
                 "fiery red leather has been tied between them. The bottom "+
                 "of the hoopak is silver clad and comes to a sharp "+
                 "point. Some runes have been ingraved in the silver. "+
                 "The weapon is so detailed that you study each of the "+
                 "creatures more closely.\n");
        wielder->update_weapon(TO);
    }

    remove_prop(OBJ_I_AIDS_ACROBATIC);
    return 0;
}

int
emote_hspin()
{
    if (!TO->query_wielded())
    {
        write("But your not wielding the "+short()+"!\n");
        return 1;
    }  
    write("With unnatural speed, you quickly spin the "+short()+ " around "+
          "in your hands.\n");
    wielder->tell_watcher("With almost unnatural speed "+QCTNAME(wielder)+
                          " spins "+HIS(TP)+ " "+short()+ " around in "+
                          HIS(TP)+ " hands.\n");
    return 1;
}

int
emote_hrun()
{
    if (!TO->query_wielded())
    {
        write("But your not wielding the "+short()+"!\n");
        return 1;
    }  
    write("You run your fingers along the shaft of the hoopak, and as you "+
          "gently caress each creature, you can hear how they seem to "+
          "purr, whisper and chirp in content with your affection.\n");

    wielder->tell_watcher(QCTNAME(wielder)+ " runs "+HIS(TP)+" fingers "+
                          "along the smooth surface of "+HIS(TP)+" hoopak, "+
                          "and a content smile spreads across "+HIS(TP)+
                          " face while "+HIS(TP)+" eyes seem to radiate "+
                          "with joy and excitement.\n");
    return 1;
}

int
emote_hswing()
{
    if (!TO->query_wielded())
    {
        write("But your not wielding the "+short()+"!\n");
        return 1;
    }  
    write("You start to swing the hoopak over your head, creating a low "+
          "sound at fist that slowly rises to the deafening magnitude of "+
          "a thousand voices united in a single terrifying roar.\n");

    wielder->tell_watcher(QCTNAME(wielder)+ " starts to swing "+HIS(TP)+
                          " hoopak over "+HIS(TP)+" head, creating a low "+
                          "sound at fist that slowly rises to the "+
                          "deafening magnitude of a thousand voices united "+
                          "in a single terrifying roar.\n");
    return 1;
}


int
hfire_stops()
{
    write("You finish your dance and the flames slowly die out. The piece "+
          "of fiery leather reappears whole and unharmed.\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " finishes "+HIS(TP)+" dance, "+
                          "and the flames slowly die out. The piece of red "+
                          "leather reappears whole and unharmed.\n");
    return 1;
}

int
emote_hfire()
{
    if (!TO->query_wielded())
    {
        write("But your not wielding the "+short()+"!\n");
        return 1;
    }  
    write("You dance around twirling the hoopak around in the air, and "+
          "flames appear from the gold dragon's mouth and the beak of the "+
          "phoenix, changing the fiery red leather tied between them into "+
          "a bright flare, which creates a captivating trail of light.\n");

    wielder->tell_watcher(QCTNAME(wielder)+ " dances around, twirling "+
                          HIS(TP)+" hoopak around in the air. Flames "+
                          "appear from the gold dragon's mouth and the "+
                          "beak of the phoenix that adorn the two branches "+
                          "on the forked top of "+HIS(TP)+" hoopak, "+
                          "changing the piece of fiery red leather tied "+
                          "between them into a bright flare, which creates "+
                          "a captivating trail of light in the air.\n");

    set_alarm(2.5,0.0, &hfire_stops());
    return 1;
}

int
items_study(string str)
{
    if (L(str) == "creatures" || L(str) == "the creatures")
    {
        write("The carved minuature creatures on the hoopak must count "+
              "many thousands. Inbetween the rabbits, foxes, cats, pigeons "+
              "and other animals you spot several unicorns, faeries, "+
              "merfolk, pegasi, griffons and a horde of other creatures, "+
              "some of which you don't even recognize.\n");
        return 1;
    }
    if (L(str) == "rabbits" || L(str) == "the rabbits")
    {
        write("You spot several adorable rabbits among the animals.\n");
        return 1;
    }
    if (L(str) == "foxes" || L(str) == "the foxes")
    {
        write("A band of foxes is chasing some unknown prey near the "+
              "bottom of the hoopak.\n");
        return 1;
    }
    if (L(str) == "unicorns" || L(str) == "the unicorns")
    {
        write("A male and female unicorn adorns the hoopak near the top of "+
              "the shaft. A young foal is standing close to its mother. "+
              "The unicorns have coats of pure white hair, and the male "+
              "has deep blue eyes, while the female eyes are a fiery pink. "+
              "Both adults have long ivory-coloured horns growing from "+
              "their foreheads, while the foal's is just a little bump.\n");
        return 1;
    }
    if (L(str) == "faeries" || L(str) == "the faeries")
    {
        write("There are faeries placed seemingly at random all along the "+
              "shaft of the hoopak. Some are partially hidden between the "+
              "creatures, while others enjoy themselves in dancing "+
              "groups.\n");
        return 1;
    }
    if (L(str) == "merfolk" || L(str) == "the merfolk")
    {
        write("A group of mermen and mermaids. They look exactly like "+
              "humans except for the tail with a large fin that has "+
              "replaced the legs.\n");
        return 1;
    }
    if (L(str) == "pegasi" || L(str) == "the pegasi")
    {
        write("These winged horses seems to be in the middle of an "+
              "airborne dance or play.\n");
        return 1;
    }
    if (L(str) == "griffons" || L(str) == "the griffons")
    {
        write("These avian creatures are half-lion, half-eagle. Their "+
              "head, upper torso and forelegs are that of an eagle and "+
              "are covered in golden feathers. Large wings rise from "+
              "their backs. The rear end and its muscular hind legs is "+
              "that of a lion and is covered with a dusky yellow fur. A "+
              "lion's tail hangs down from the griffons' powerful rear "+
              "haunches.\n");
        return 1;
    }
    if (L(str) == "cats" || L(str) == "the cats")
    {
        write("Near the middle of the shaft you see a small fluffy orange "+
              "kitten, a cream and chocolate colored cat, and somewhat "+
              "hidden in the shadows behind the other two cats you see "+
              "a third larger cat.\n");
        return 1;
    }
    if (L(str) == "dragon" || L(str) == "the dragon" ||
        L(str) == "gold dragon" || L(str) == "the gold dragon")
    {
        write("A huge metallic dragon with golden scales decorates one of "+
              "the branches on the forked top of the hoopak. There is a "+
              "wise glimpse in its yellow eyes, and the dragon looks noble "+
              "and majestic. You can't help but feel an aura of goodness "+
              "radiating from it.\n");
        return 1;
    }
    if (L(str) == "phoenix" || L(str) == "the phoenix")
    {
        write("This is a perfect carving of a giant multi-coloured bird. "+
              "It is covered in bright multi-coloured feathers, "+
              "including violet, scarlet, crimson and flaming orange. Its "+
              "beak and claws are violet-blue, and its eyes are a deep "+
              "glowing ruby colour.\n");
        return 1;
    }
    if (L(str) == "pigeons" || L(str) == "the pigeons")
    {
        write("Two pigeons are nested on the back of a black mare. Each "+
              "one appears to be staring into the eyes of the other.\n");
        return 1;
    }
    if (L(str) == "runes" || L(str) == "the runes" ||
        L(str) == "silver" || L(str) == "the silver")
    {
        write("Most of these runes are unknown to you, and no matter how "+
              "hard you try, you cannot seem to focus on them for long "+
              "enough to study them. You do however manage to read the "+
              "words 'hswing', 'hrun', 'hspin' and 'hfire' between the "+
              "runes.\n");
        return 1;
    }
    if (L(str) == "second cat" || L(str) == "study brown cat" ||
        L(str) == "study cream coloured cat" ||
        L(str) == "study chocolate coloured cat" ||
        L(str) == "the second cat")
    {
        write("This cat looks a lot like a siamese, except for its "+
              "long-haired fur. He has a cream-coloured body while "+
              "his ears, face and tale have a nice dark chocolate "+
              "brown colour. A pair of sparkly blue eyes stand out "+
              "from the dark brown colour of his face.");
        return 1;
    }
    if (L(str) == "kitten" || L(str) == "the kitten" || 
        L(str) == "orange kitten" || L(str) == "the orange kitten")
    {
        write("This is a little orange kitten. It looks slightly chubby, "+
              "and is rolled up in a ball, fast asleep. It looks very "+
              "content.\n");
        return 1;
    }
    if (L(str) == "larger cat" || L(str) == "the larger cat" ||
        L(str) == "lynx" || L(str) == "the lynx" ||
        L(str) == "third cat" || L(str) == "the third cat")
    {
        write("This cat is almost completely hidden by the shadows behind "+
              "the two other cats. Upon closer examination you realize "+
              "that this cat is much too large to be a normal cat. It has "+
              "a sleek, compact and muscular body. Its forepaws are "+
              "unsually large and its hind legs look quite powerful. It "+
              "also has tufted ears and cheeks. It has an incredibly "+
              "intelligent glimpse in its eyes, and you realize that this "+
              "cat must be a lynx.\n");
        return 1;
    }
    if (L(str) == "mare" || L(str) == "the mare")
    {
        write("This black mare stands among a few other horses. It has a "+
              "shiny coat of completely black hair, except for one white "+
              "spot on its forehead.\n");
        return 1;
    }
    if (L(str) == "lion" || L(str) == "the lion")
    {
        write("Somewhere between the creatures you spot a proud looking "+
              "male lion. It has yellow fur, and a large golden brown mane "+
              "encircles its head. This fearsome predator looks ready to "+
              "jump at any enemy.");
        return 1;
    }
    write("Study what? The creatures or a specific one?\n");
    return 1;
}

void
load_hoopak()
{
    TP->catch_msg("You proceed to load the hoopak.\n");
    tell_room(E(TP), C(QCTNAME(TP)) + " sticks " +
      TP->query_possessive() + " tongue out as " +
      TP->query_pronoun() + " loads the hoopak with a pebble.\n",TP);
}

void
aim(string b, object target)
{
    TP->catch_msg("You start to aim the hoopak at " + QTNAME(target) +
      " and hope they stand still long enough for you to get them in your " +
      "sight.\n");
    target->catch_msg(QCTNAME(TP) + " aims the hoopak in your direction.\n");
    tell_room(E(TP), QCTNAME(TP) +" aims the hoopak in " + QTNAME(target) +
      "'s general direction.\n", ({TP, target}));
}

void
shoot(string b, object target)
{
    TP->catch_msg("You let the pebble fly towards " + QTNAME(target) + ".\n"+
      "The pebble hits " + target->query_objective() + " harmlessly.\n");
    target->catch_msg(C(QCTNAME(TP)) + " lets the pebble fly from the "+
      "hoopak.\nIt hits you harmlessly and falls to the ground.\n");
    tell_room(E(TP), C(QCTNAME(TP)) + " let the pebble go and fly towards "+
      QCTNAME(target) +".\nThe pebble hits " + target->query_objective() +
      " harmlessly and falls to the ground.\n",({TP,target}));
}
void
stop_shoot()
{
    remove_alarm(alload);
    remove_alarm(alaim);
    remove_alarm(alshoot);
}

int
shoot_player(string str)
{
    string self;
    string a,b;int i;
    object * temparray;
    object target;
    object obj;
    /* If this code look fimiliar .. Well it should I was wonder around
    mackers workroom one day and when i got back home LO and Behold!
    this code was in one of my pouches so i decided to use it.. after
    all what good is code that is not in use :)
     Erine
    "Borrowed from code by macker feather.c"
    */
    if(present("hoopak", TP))
    {
        if(!(interactive(E(TO))))
        {
            write("Why would you want to shoot that?!?!\n");
            return 1;
        }

        if((!strlen(str) || !str))
        {
            write("Well darn it all anyways. What are you gonna shoot?\n");
            return 1;
        }

        i = sscanf(str, "%s with %s", a, b);
        if(!((a)&&((b=="hoopak")||(b=="staff"))))
        {
            NF("Shoot who with what?!?\n");
            return 0;
        }
        temparray = (find_str_in_object(a, E(E(TO))));
        if(sizeof(temparray) == 0)
            target = 0;
        else
            target = temparray[0];
        if((i)&&((b=="hoopak")||(b=="staff"))&&((a=="me")||(a=="myself")))
            target = TP;
        if(!(living(target)))
        {
            NF("Seems like a useless idea to shoot that doesn't it??\n");
            return 0;
        }
        if((i)&&(((a=="me")||(a=="myself"))&&((b=="hoopak")||(b=="staff"))))

            if(!(((b=="hoopak")||(b=="staff"))&&(i)&&(target)))
            {
                NF("Shoot who with what?\n");
                return 0;
            }
        if(target==TP)
        {
            if(TP->query_gender() == 0)
                self = "himself";
            else
            if(TP->query_gender() == 1)
                self = "herself";
            else
                self = "itself";
            write("This feat seems quite hard to accomplish not to mention "+
              "the fact you may miss and make someone lose an eye! "+
              "You decide not to do this.\n");
            return 1;
        }
        NF("Shoot who with what?\n");
        if(!((target)&&(i)))
            return 0;
        if(TP->query_met(target))
            b = QCTNAME(target);
        TP->catch_msg("You bend down and pick up a pebble from the "+
                      "ground.\n");
        tell_room(E(TP),QCTNAME(TP) + " bends down and picks up a pebble "+
                  "from the ground.\n",TP);
        alload = set_alarm(4.0,0.0,"load_hoopak");
        alaim = set_alarm(6.0,0.0,"aim",a,target);
        alshoot = set_alarm(8.0,0.0,"shoot",a,target);
        obj = clone_object("std/paralyze");
        obj->set_stop_object(tstaff);
        obj->set_stop_fun("stop_shoot");
        obj->set_remove_time(8);
        obj->set_fail_message("You are trying to shoot somebody with your "+
          "hoopak. Maybe you should 'stop' before trying anything else.\n");
        obj->set_stop_message("You stop trying to shoot people with your "+
                              "hoopak.\n");
        obj->move(TP);
        return 1;
    }
    write("If you want to shoot someone you first have to have something "+
          "to shoot with.\n");
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{

    object blinding;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    switch(phurt)
    {
    case -1:
    case -2:
        if (!wielder->query_option(OPT_GAG_MISSES))
        {
            wielder->catch_msg("The speed of your attack makes you spin "+
                "around as you just miss " +QTNAME(enemy)+ " with your " +
                short() + ".\n");
        }
        if (!enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(wielder) + " makes a quick spin as "+
                HE(wielder)+ " misses you completely with his with "+
                 HIS(wielder)+ " " + short() + ".\n");
        }
        wielder->tell_watcher_miss(QCTNAME(wielder) + " makes a quick spin "+
            "as "+HE(wielder)+ " misses "+QTNAME(enemy) + " with " +
            POSSESSIVE(wielder)+ " " +short()+ ".\n",
            enemy);
        break;

    case 0..7:
        wielder->catch_msg("You lightly touch the "+hdesc+" of "+
          QTNAME(enemy)+ " with your "+short()+" and you feel certain you "+
          "see a short flash of movement as the hoopak touches "+
          HIM(enemy)+".\n");
        enemy->catch_msg(QCTNAME(wielder) + " lightly touches your "+hdesc+
          "with " +POSSESSIVE(wielder)+ " " +short() + ", and you feel a "+
          "small sting.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " lightly touches the "+hdesc+
          " of " +QTNAME(enemy)+ " with " +HIS(wielder)+ " " +short()+
          ".\n",enemy);
        break;

    case 8..18:
        wielder->catch_msg("As you hit the "+hdesc+" of "+QTNAME(enemy)+
          " with your " +short()+ ", a pair of claws appear from it, grazing "+
          HIM(enemy)+ " lightly.\n");
        enemy->catch_msg("As " +QTNAME(wielder)+" hits your "+hdesc+" with "+
          HIS(wielder)+ " "+short()+", you feel some claws grazing you "+
          "lightly.\n");
        wielder->tell_watcher("As "+QTNAME(wielder)+ " hits the "+hdesc+
          " of "+QTNAME(enemy)+ " with "+HIS(wielder)+ " " +short()+ ", a "+
          "pair of claws appear from it, grazing "+HIM(enemy)+
          " lightly.\n",enemy);
        break;

    case 19..31:
        wielder->catch_msg("You thrust your "+short()+ " at "+
          QTNAME(enemy)+ ", and tiny faeries dart out from all along the "+
          "shaft, stabbing and slashing "+HIM(enemy)+ " with their tiny "+
          "weapons before returning to the hoopak.\n");
        enemy->catch_msg(QCTNAME(wielder) + " thrusts "+HIS(wielder)+ " "+
          short()+ " at " +QTNAME(enemy)+ ", and tiny faeries dart out from "+
          "all along the shaft, stabbing and slashing "+HIM(enemy)+ " "+
          hdesc+" with this tiny weapons before returning to the hoopak.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " thrusts "+HIS(wielder)+" "+
          short()+ " at "+QTNAME(enemy)+ ", and tiny faeries dart out from "+
          "all along the shaft, stabbing and slashing "+HIM(enemy)+ " "+
          hdesc+" with their tiny weapons before returning to the "+
          "hoopak.\n",enemy);
        break;

    case 32..47:
        wielder->catch_msg("Your "+short()+ " swings close by "+
          QTNAME(enemy)+", and talons emerge from its shaft, "+
          "scratching "+HIM(enemy)+ " "+hdesc+" viciously.\n");
        enemy->catch_msg("As "+QCTNAME(wielder) + " swings " +HIS(wielder)+
          " " +short()+ " close by you, talons emerge from its shaft, "+
          "scratching your "+hdesc+ " viciously.\n");
        wielder->tell_watcher("As "+QCTNAME(wielder)+ " swings "+HIS(wielder)+
          " "+short()+ " close by "+QTNAME(enemy)+ ", talons emerge from "+
          "its shaft, scratching his "+hdesc+ " viciously.\n",enemy);
        break;

    case 48..61:
        wielder->catch_msg("You thumb your "+short()+ " at "+
          QTNAME(enemy)+", and a tentacle shoots from it, wrapping itself "+
          "around "+HIS(enemy)+ " "+hdesc+", leaving wounds as you tear it "+
          "lose and pull back your hoopak.\n");
        enemy->catch_msg("As "+QCTNAME(wielder) + " thumbs " +HIS(wielder)+
          " " +short()+ " at you, and a tentacle shoots from it, wrapping "+
          "itself around your "+hdesc+", leaving wounds as "+HE(wielder)+
          "tears it lose and pulls back "+HIS(wielder)+" hoopak.\n");
        wielder->tell_watcher(QCTNAME(wielder)+ " thumbs the "+hdesc+
          " of "+QTNAME(enemy)+ " with "+HIS(wielder)+" "+short()+
          ", and a tentacle shoots from it, wrapping itself around it, "+
          "leaving wounds as "+HE(wielder)+" tears it lose, pulling back "+
          HIS(wielder)+ " hoopak.\n",enemy);
        break;

    case 62..88:
        wielder->catch_msg("You thrust at "+QTNAME(enemy)+", with your "+
          short()+ ", and a lion's head suddenly grows from it, and bites "+
          "deeply into his "+hdesc+".\n");
        enemy->catch_msg(QCTNAME(wielder) + " thrusts " +HIS(wielder)+
          " " +short()+ " at you, and a lion's head suddenly grows from "+
          "it biting deeply into your "+hdesc+".\n");
        wielder->tell_watcher(QCTNAME(wielder)+ " thrusts his "+short()+
          " at "+QTNAME(enemy)+ ", and a lion's head suddenly grows from "+
          "it, and bites deeply into "+HIS(enemy)+" "+hdesc+ ".\n",enemy);
        break;

    default:
        wielder->catch_msg("As you swing at " +QTNAME(enemy)+
          " with your " +short()+ ", one of the unicorns comes "+
          "to life and impales "+HIS(enemy)+" with its ivory horn, "+
          "making a mortal wound!\n");
        enemy->catch_msg("As "+QCTNAME(wielder)+ " swings " +
          POSSESSIVE(wielder)+ " " +short()+ " at you, one of the "+
          "unicorns adorning it comes to life and impales your "+
          hdesc+" with its ivory horn, making a mortal wound!\n");
        wielder->tell_watcher("As "+QCTNAME(wielder) + " swings " +
          POSSESSIVE(wielder)+ " " +short()+ " at "+QTNAME(enemy)+
          " one of the unicorns adorning "+QCTNAME(wielder)+"'s "+short()+
          " comes to life and impales "+
          HIS(enemy)+ " "+hdesc+" with its ivory horn, making "+
          "a mortal wound!\n",enemy);
        break;
    }
    return 1;
}

/*
 * Function name: remove_broken
 * Description  : The weapon got broken so the player has to stop
 *                wielding it.
 * Arguments    : int silent - true if no message is to be genereated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

     return;
}


/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_dull(int du)
{
    return 0;
}


void
init()
{
    ::init();
    add_action("shoot_player", "shoot");
    add_action("emote_hspin", "hspin");
    add_action("emote_hswing", "hswing");
    add_action("emote_hrun", "hrun");
    add_action("emote_hfire", "hfire");
    add_action("items_study", "study");

}


