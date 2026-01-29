
/*
 * ritual_chamber.c
 *
 * Ritual chamber for the Spirit Circle of Psuchae Temple
 * This room is used to create components for spells from
 * other items. First a player must <enter pentagram>, then
 * <insert (gemname)>, <place (itemname)>, <light candles>,
 * then finally <create (new component name)>.
 *
 * Copyright (C): Jaacar (Mike Phipps), August 2nd, 2003.
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>

#include "defs.h"
#include SPIRIT_HEADER

#define I_LIT_THE_CANDLES  "_i_lit_the_candles"
#define I_INSERTED_GEM     "_i_inserted_gem"
#define I_PLACED_ITEM      "_i_placed_item"
#define I_DESIGNATED_WEP   "_i_designated_weapon"
#define I_AM_IN_PENTAGRAM  "_i_am_in_pentagram"

int in_pent = 0;
string gem_string = "There is nothing in the indentation.";
string pentagram_string = "There is no item placed in the pentagram.";
string weapon_string = "";
string candles_string = "The candles are extinguished.";
string person_pentagram = "There is nobody in the pentagram.";
string robe_hook = "There is a robe hanging on the hook.";

object placed_item;
object designated_weapon;
object inserted_gem;

int 
query_prevent_snoop()
{
    return 1;
}

void
create_room()
{
    set_short("Ritual chamber");
    set_long("You are in the Ritual Chamber. This chamber looks "+
        "like half of a circle curving away from you to the north. "+
        "The walls of this chamber are very smooth and painted "+
        "midnight black. There are no windows at all in this area. "+
        "The only light in this room comes from a small lantern hanging "+
        "on the wall. There are five white candles arranged on the floor "+
        "at triangular points of the pentagram drawn on the black stone "+
        "floor. There is a hook hanging to one side of the set of maple "+
        "double doors set in the southern wall.\n");

    add_item("hook","There is a hook hanging to one side of the set of "+
        "maple double doors set in the southern wall. @@hook_desc@@\n");
    add_item(({"lantern","small lantern"}),"There is a small lantern "+
        "hanging on the wall. It is the only light source in this "+
        "entire room, unless the candles are lit.\n");
    add_item(({"triangular point", "triangular points"}), "At each "+
        "of the five triangular points of the pentagram on the floor "+
        "there is a white candle.\n");
    add_item("light", "The only light in the whole chamber is coming "+
        "from the small lantern hanging from the wall.\n");
    add_item(({"floor", "stone floor","black stone floor","black floor"}),
        "The floor is made of stone and is painted the same midnight "+
        "black colour that the walls and ceiling are painted. In the "+
        "middle of the floor is a pentagram.\n");
    add_item(({"roof", "ceiling"}), "The ceiling of this chamber is "+
        "painted the same midnight black as the walls and floor are.\n");
    add_item("indentation","This indentation looks like you could insert "+
        "a gem into it. @@indent_gem@@\n");
    add_item("pentagram","There is a pentagram drawn in the middle "+
        "of the black stone floor. At each one of the triangular points "+
        "there is a white candle. In the top-most triangular point is "+
        "an indentation. @@pentagram_person@@ @@pentagram_item@@ "+
        "@@pentagram_weapon@@\n");
    add_item(({"window", "windows"}), "There are no windows in "+
        "this chamber.\n");
    add_item(({"wall", "walls"}), "The walls of this chamber are "+
        "very smooth to the touch and painted midnight black. They "+
        "almost absorb all light in this room.\n");
    add_item(({"candle","candles","white candle","white candles",
        "five candles","five white candles"}),"There are five white "+
        "candles placed at the triangular points of the pentagram that "+
        "has been drawn on the black stone floor. It looks like you "+
        "could light the candles. @@candles_lit@@\n");
    add_item(({"southern doors","southern door","double doors",
        "maple double doors","maple doors","north door","north doors"}),
        "These are a set of maple double doors set into the southern "+
        "wall.\n");

    IN;
    add_prop(ROOM_M_NO_TELEPORT,"This is a sacred place. You cannot use "+
        "teleportation magic here.\n");
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"great_hall","south","@@check_pentagram@@",1);
}

int
check_pentagram()
{
    if (TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        write("You are in the pentagram, you must <leave pentagram> or "
            + "<abort ritual>.\n");
        return 1;
    }

    return 0;
}

string
pentagram_person()
{
    return person_pentagram;
}

string
indent_gem()
{
    return gem_string;
}

string
pentagram_item()
{
    return pentagram_string;
}

string
pentagram_weapon()
{
    return weapon_string;
}

string
candles_lit()
{
    return candles_string;
}

string
hook_desc()
{
    return robe_hook;
}

int
do_create(string str)
{
    object gem, item, new_comp;
    string stickstaff;

    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You must be in the pentagram to perform a ritual! <enter pentagram>\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Create what? (If you are unsure what to create, visit "+
           "the library for a list of combinations)\n");
        return 0;
    }

    if (!TP->query_prop(I_LIT_THE_CANDLES))
    {
        NF("You cannot complete the ritual without lighting the candles "+
            "first! <light candles>\n");
        return 0;
    }

    if (!TP->query_prop(I_INSERTED_GEM))
    {
        NF("You cannot complete the ritual without inserting a gem into "+
           "the indentation! <insert (gemname)>\n");
        return 0;
    }

    if (!TP->query_prop(I_PLACED_ITEM))
    {
        NF("You cannot complete the ritual without placing an item in the "+
           "pentagram! <insert (itemname)>\n");
        return 0;
    }

    if (str == "skiamorfi")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "amber")
        {
            NF("You must insert an amber into the indentation!\n");
            return 0;
        }

        if (TP->query_prop(I_PLACED_ITEM) != "cranberry")
        {
            NF("You must place a cranberry into the pentagram!\n");
            return 0;
        }
        
        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is no item placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae for power.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae for power.\n");
        write("You telepathically say: I conjure thee, O Circle of Power, "+
            "that thou beest a meeting place of love and joy and truth;\n"+
            "A shield against all wickedness and evil;\nA boundary "+
            "between mortals and the realms of the Elementals;\nA rampart "+
            "and protection that shall preserve and contain the power that "+
            "we shall raise within thee.\nWherefore do I bless thee and "+
            "consecrate thee, in the name of Psuchae.\n");
        say(QCTNAME(TP)+" says telepathically: I conjure thee, O Circle "+
            "of Power, that thou beest a meeting place of love and joy "+
            "and truth;\nA shield against all wickedness and evil;\nA "+
            "boundary between mortals and the realms of the Elementals;\n"+
            "A rampart and protection that shall preserve and contain the "+
            "power that we shall raise within thee.\nWherefore do I bless "+
            "thee and consecrate thee, in the name of Psuchae.\n");
        write("You dedicated your offerings to the skiamorfi ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the skiamorfi ritual.\n");
        write("The amber in the indentation shines brightly.\n");
        say("The amber in the indentation shines brightly.\n");
        write("The cranberry rises up off the ground, and hovers over "+
            "the light shining from the amber.\n");
        say("The cranberry rises up off the ground, and hovers over "+
            "the light shining from the amber.\n");
        write("Focusing the energies of Psuchae, you wave your hands "+
            "before the offerings. They are quickly consumed by "+
            "unseen shadows and replaced with the skiamorfi component.\n");
        say("Focusing the energies of Psuchae, "+TP->query_pronoun()+
            " waves "+TP->query_possessive()+" hands before the offerings. "+
            "They are quickly consumed by unseen shadows and replaced with "+
            "the skiamorfi component.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"skiamorfi_comp");
        new_comp->move(TP);
        write("You take the skiamorfi component.\n");
        say(QCTNAME(TP)+" takes the skiamorfi component.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("You telepathically say: Air, Fire, Water, Earth, and Spirit.\n"+
            "Elements of astral birth, I call you now;\nAttend to me! "+
            "In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        say(QCTNAME(TP)+" telepathically says: Air, Fire, Water, Earth, "+
            "and Spirit.\nElements of astral birth, I call you now;\nAttend "+
            "to me! In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }

    if (str == "sfyri")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "garnet")
        {
            NF("You must insert an garnet into the indentation!\n");
            return 0;
        }

        if (TP->query_prop(I_PLACED_ITEM) != "heart")
        {
            NF("You must place a heart into the pentagram!\n");
            return 0;
        }

        if (!TP->query_prop(I_DESIGNATED_WEP))
        {
            NF("You cannot complete the ritual without designating a "+
               "weapon to place in the pentagram! <designate (weaponname)>\n");
            return 0;
        }

        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is no item placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);

        designated_weapon->remove_object();
        weapon_string = "";
        TP->remove_prop(I_DESIGNATED_WEP);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae for power.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae for power.\n");
        write("You telepathically say: I conjure thee, O Circle of Power, "+
            "that thou beest a meeting place of love and joy and truth;\n"+
            "A shield against all wickedness and evil;\nA boundary "+
            "between mortals and the realms of the Elementals;\nA rampart "+
            "and protection that shall preserve and contain the power that "+
            "we shall raise within thee.\nWherefore do I bless thee and "+
            "consecrate thee, in the name of Psuchae.\n");
        say(QCTNAME(TP)+" says telepathically: I conjure thee, O Circle "+
            "of Power, that thou beest a meeting place of love and joy "+
            "and truth;\nA shield against all wickedness and evil;\nA "+
            "boundary between mortals and the realms of the Elementals;\n"+
            "A rampart and protection that shall preserve and contain the "+
            "power that we shall raise within thee.\nWherefore do I bless "+
            "thee and consecrate thee, in the name of Psuchae.\n");
        write("You dedicated your offerings to the sfyri ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the sfyri ritual.\n");
        write("The garnet in the indentation shines brightly.\n");
        say("The garnet in the indentation shines brightly.\n");
        write("The heart rises up off the ground, and hovers over "+
            "the light shining from the garnet.\n");
        say("The heart rises up off the ground, and hovers over "+
            "the light shining from the garnet.\n");
        write("The weapon begins to spin "+
            "around in circles in the pentagram.\n");
        say("The weapon begins to spin "+
            "around in circles in the pentagram.\n");
        write("Focusing the energies of Psuchae, you wave your hands "+
            "before the offerings. They are quickly consumed by "+
            "unseen shadows and replaced with the sfyri component.\n");
        say("Focusing the energies of Psuchae, "+TP->query_pronoun()+
            " waves "+TP->query_possessive()+" hands before the offerings. "+
            "They are quickly consumed by unseen shadows and replaced with "+
            "the sfyri component.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"sfyri_comp");
        new_comp->move(TP);
        write("You take the sfyri component.\n");
        say(QCTNAME(TP)+" takes the sfyri component.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("You telepathically say: Air, Fire, Water, Earth, and Spirit.\n"+
            "Elements of astral birth, I call you now;\nAttend to me! "+
            "In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        say(QCTNAME(TP)+" telepathically says: Air, Fire, Water, Earth, "+
            "and Spirit.\nElements of astral birth, I call you now;\nAttend "+
            "to me! In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }
    
    if (str == "anakalo")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "chalcedony")
        {
            NF("You must insert an chalcedony into the indentation!\n");
            return 0;
        }

        if (TP->query_prop(I_PLACED_ITEM) != "breadroot")
        {
            NF("You must place some breadroot into the pentagram!\n");
            return 0;
        }
                
        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is no item placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae for power.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae for power.\n");
        write("You telepathically say: I conjure thee, O Circle of Power, "+
            "that thou beest a meeting place of love and joy and truth;\n"+
            "A shield against all wickedness and evil;\nA boundary "+
            "between mortals and the realms of the Elementals;\nA rampart "+
            "and protection that shall preserve and contain the power that "+
            "we shall raise within thee.\nWherefore do I bless thee and "+
            "consecrate thee, in the name of Psuchae.\n");
        say(QCTNAME(TP)+" says telepathically: I conjure thee, O Circle "+
            "of Power, that thou beest a meeting place of love and joy "+
            "and truth;\nA shield against all wickedness and evil;\nA "+
            "boundary between mortals and the realms of the Elementals;\n"+
            "A rampart and protection that shall preserve and contain the "+
            "power that we shall raise within thee.\nWherefore do I bless "+
            "thee and consecrate thee, in the name of Psuchae.\n");
        write("You dedicated your offerings to the anakalo ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the anakalo ritual.\n");
        write("The chalcedony in the indentation shines brightly.\n");
        say("The chalcedony in the indentation shines brightly.\n");
        write("The breadroot rises up off the ground, and hovers over "+
            "the light shining from the chalcedony.\n");
        say("The breadroot rises up off the ground, and hovers over "+
            "the light shining from the chalcedony.\n");
        write("Focusing the energies of Psuchae, you wave your hands "+
            "before the offerings. They are quickly consumed by "+
            "unseen shadows and replaced with the anakalo component.\n");
        say("Focusing the energies of Psuchae, "+TP->query_pronoun()+
            " waves "+TP->query_possessive()+" hands before the offerings. "+
            "They are quickly consumed by unseen shadows and replaced with "+
            "the anakalo component.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"anakalo_comp");
        new_comp->move(TP);
        write("You take the anakalo component.\n");
        say(QCTNAME(TP)+" takes the anakalo component.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("You telepathically say: Air, Fire, Water, Earth, and Spirit.\n"+
            "Elements of astral birth, I call you now;\nAttend to me! "+
            "In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        say(QCTNAME(TP)+" telepathically says: Air, Fire, Water, Earth, "+
            "and Spirit.\nElements of astral birth, I call you now;\nAttend "+
            "to me! In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }

    if (str == "metaballo")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "red spinel")
        {
            NF("You must insert a red spinel into the indentation!\n");
            return 0;
        }

        if (TP->query_prop(I_PLACED_ITEM) != "sargassum")
        {
            NF("You must place some sargassum into the pentagram!\n");
            return 0;
        }

        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is no item placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae for power.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae for power.\n");
        write("You telepathically say: I conjure thee, O Circle of Power, "+
            "that thou beest a meeting place of love and joy and truth;\n"+
            "A shield against all wickedness and evil;\nA boundary "+
            "between mortals and the realms of the Elementals;\nA rampart "+
            "and protection that shall preserve and contain the power that "+
            "we shall raise within thee.\nWherefore do I bless thee and "+
            "consecrate thee, in the name of Psuchae.\n");
        say(QCTNAME(TP)+" says telepathically: I conjure thee, O Circle "+
            "of Power, that thou beest a meeting place of love and joy "+
            "and truth;\nA shield against all wickedness and evil;\nA "+
            "boundary between mortals and the realms of the Elementals;\n"+
            "A rampart and protection that shall preserve and contain the "+
            "power that we shall raise within thee.\nWherefore do I bless "+
            "thee and consecrate thee, in the name of Psuchae.\n");
        write("You dedicated your offerings to the metaballo ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the metaballo ritual.\n");
        write("The red spinel in the indentation shines brightly.\n");
        say("The red spinel in the indentation shines brightly.\n");
        write("The sargassum rises up off the ground, and hovers over "+
            "the light shining from the red spinel.\n");
        say("The sargassum rises up off the ground, and hovers over "+
            "the light shining from the red spinel.\n");
        write("Focusing the energies of Psuchae, you wave your hands "+
            "before the offerings. They are quickly consumed by "+
            "unseen shadows and replaced with the metaballo component.\n");
        say("Focusing the energies of Psuchae, "+TP->query_pronoun()+
            " waves "+TP->query_possessive()+" hands before the offerings. "+
            "They are quickly consumed by unseen shadows and replaced with "+
            "the metaballo component.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"metaballo_comp");
        new_comp->move(TP);
        write("You take the metaballo component.\n");
        say(QCTNAME(TP)+" takes the metaballo component.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("You telepathically say: Air, Fire, Water, Earth, and Spirit.\n"+
            "Elements of astral birth, I call you now;\nAttend to me! "+
            "In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        say(QCTNAME(TP)+" telepathically says: Air, Fire, Water, Earth, "+
            "and Spirit.\nElements of astral birth, I call you now;\nAttend "+
            "to me! In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }

/*    if (str == "energia")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "sapphire")
        {
            NF("You must insert a sapphire into the indentation!\n");
            return 0;
        }

        if (TP->query_prop(I_PLACED_ITEM) != "sea bubble")
        {
            NF("You must place some sea bubble into the pentagram!\n");
            return 0;
        }

        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is nothing placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae for power.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae for power.\n");
        write("You telepathically say: I conjure thee, O Circle of Power, "+
            "that thou beest a meeting place of love and joy and truth;\n"+
            "A shield against all wickedness and evil;\nA boundary "+
            "between mortals and the realms of the Elementals;\nA rampart "+
            "and protection that shall preserve and contain the power that "+
            "we shall raise within thee.\nWherefore do I bless thee and "+
            "consecrate thee, in the name of Psuchae.\n");
        say(QCTNAME(TP)+" says telepathically: I conjure thee, O Circle "+
            "of Power, that thou beest a meeting place of love and joy "+
            "and truth;\nA shield against all wickedness and evil;\nA "+
            "boundary between mortals and the realms of the Elementals;\n"+
            "A rampart and protection that shall preserve and contain the "+
            "power that we shall raise within thee.\nWherefore do I bless "+
            "thee and consecrate thee, in the name of Psuchae.\n");
        write("You dedicated your offerings to the energia ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the energia ritual.\n");
        write("The sapphire in the indentation shines brightly.\n");
        say("The sapphire in the indentation shines brightly.\n");
        write("The sea bubble rises up off the ground, and hovers over "+
            "the light shining from the sapphire.\n");
        say("The sea bubble rises up off the ground, and hovers over "+
            "the light shining from the sapphire.\n");
        write("Focusing the energies of Psuchae, you wave your hands "+
            "before the offerings. They are quickly consumed by "+
            "unseen shadows and replaced with the energia component.\n");
        say("Focusing the energies of Psuchae, "+TP->query_pronoun()+
            " waves "+TP->query_possessive()+" hands before the offerings. "+
            "They are quickly consumed by unseen shadows and replaced with "+
            "the energia component.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"energia_comp");
        new_comp->move(TP);
        write("You take the energia component.\n");
        say(QCTNAME(TP)+" takes the energia component.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("You telepathically say: Air, Fire, Water, Earth, and Spirit.\n"+
            "Elements of astral birth, I call you now;\nAttend to me! "+
            "In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        say(QCTNAME(TP)+" telepathically says: Air, Fire, Water, Earth, "+
            "and Spirit.\nElements of astral birth, I call you now;\nAttend "+
            "to me! In the Circle, rightly cast, Safe from curse or blast, "+
            "I call you now, attend to me, protect me, close this Circle in "+
            "the name of Psuchae!\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }
*/
    if (str == "Psuchaestaff")
    {
        if (TP->query_prop(I_INSERTED_GEM) != "black diamond")
        {
            NF("You must insert a black diamond into the indentation!\n");
            return 0;
        }

        if ((TP->query_prop(I_PLACED_ITEM) != "stick") && 
            (TP->query_prop(I_PLACED_ITEM) != "staff"))
        {
            NF("You must place a stick or staff into the pentagram!\n");
            return 0;
        }

        stickstaff = TP->query_prop(I_PLACED_ITEM);
        inserted_gem->remove_object();
        gem_string = "There is nothing in the indentation.";
        TP->remove_prop(I_INSERTED_GEM);
        
        placed_item->remove_object();
        pentagram_string = "There is nothing placed in the pentagram.";
        TP->remove_prop(I_PLACED_ITEM);
        
        candles_string = "The candles are extinguished.";
        TP->remove_prop(I_LIT_THE_CANDLES);
        
        write("Bowing your head in reverence for a moment, you pray out "+
            "to Psuchae with your offerings.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
            "for a moment, and prays out to Psuchae with "+
            TP->query_possessive()+" offerings.\n");
        write("You dedicated your offerings to the Psuchaestaff ritual.\n");
        say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
            "to the Psuchaestaff ritual.\n");
        write("The black diamond in the indentation shines brightly.\n");
        say("The black diamond in the indentation shines brightly.\n");
        write("The "+stickstaff+" rises up off the ground, and hovers over "+
            "the light shining from the black diamond.\n");
        say("The "+stickstaff+" rises up off the ground, and hovers over "+
            "the light shining from the black diamond.\n");
        write("Your offerings are quickly consumed by "+
            "unseen shadows and replaced with a staff.\n");
        say("The offerings are quickly consumed by unseen shadows and "+
            "replaced with a staff.\n");
        new_comp = clone_object(SPIRIT_OBJECTS+"psuchae_staff");
        new_comp->move(TP);
        write("You take the staff.\n");
        say(QCTNAME(TP)+" takes the staff.\n");
        write("You bow your head in reverence once more, thanking Psuchae "+
            "for the gift bestowed upon you.\n");
        say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
            "in reverence, thanking Psuchae for he gift bestowed upon "+
            TP->query_objective()+".\n");
        write("The candles extinguish themselves.\n");
        say("The candles extinguish themeselves.\n");
        return 1;
    }

    write("There is no "+str+" ritual to perform.\n");
    return 1;
}

int
do_designate(string str)
{
    object weapon;
    
    weapon = present(str, TP);
    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You must be in the pentagram to perform a ritual! <enter pentagram>\n");
        return 0;
    }

    if (!str)
    {
        NF("Designate what? A weapon? <designate (weaponname)>\n");
        return 0;
    }

    if (!weapon->check_weapon())
    {
        NF("You must designate a weapon!\n");
        return 0;
    }

    if (weapon->query_pen() <= 9)
    {
        NF("You must designate a stronger weapon than that.\n");
        return 0;
    }

    if (weapon->query_hit() <= 9)
    {
        NF("You must designate a stronger weapon than that.\n");
        return 0;
    }
    
    weapon_string = "There is a "+weapon->query_short()+" placed in the pentagram.";
    weapon->move(environment(TP));
    weapon->set_no_show_composite(1);
    weapon->add_prop(OBJ_M_NO_GET,"You cannot take this weapon, it "+
        "is being used in a ritual.\n");
    designated_weapon = weapon;
    write("You put the "+weapon->query_short()+" into the pentagram.\n");
    say(QCTNAME(TP)+" places a "+weapon->query_short()+" into the pentagram.\n");
    TP->add_prop(I_DESIGNATED_WEP,(weapon->query_short()));
    return 1;
}

object
herb_present(string name, object container)
{
    object * herbs;
    
    if (!objectp(container))
    {
        return 0;
    }
    
    herbs = FILTER_HERB_OBJECTS(all_inventory(container));
    herbs = filter(herbs, &operator(==)(name) @ &->query_herb_name());
    
    if (pointerp(herbs) && sizeof(herbs))
    {
        return herbs[0];
    }
}

int
do_insert(string str)
{
    object gem_heap, gem;
    int heap_size;

    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You must be in the pentagram to perform a ritual! <enter pentagram>\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Insert what? A gem into the indentation? <insert (gemname)>\n");
        return 0;
    }

    if (present("_psuchae_staff_",TP))
    {
        NF("You already have a Staff of Psuchae. You cannot "+
            "create another.\n");
        return 0;
    }

    if (parse_command(str, ({}), 
        "[the] [yellow] 'amber' [in] [into] [the] [indentation]"))
    {
        if (!present("amber",TP))
        {
            NF("You do not have an amber!\n");
            return 0;
        }

        gem_string = "There is an amber placed in the indentation.";
        gem_heap = present("amber",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the amber, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put an amber into the indentation.\n");
        say(QCTNAME(TP)+" inserts an amber into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"amber");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [striped] 'chalcedony' [in] [into] [the] [indentation]"))
    {
        if (!present("chalcedony",TP))
        {
            NF("You do not have a chalcedony!\n");
            return 0;
        }

        gem_string = "There is a chalcedony placed in the indentation.";
        gem_heap = present("chalcedony",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the chalcedony, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put a chalcedony into the indentation.\n");
        say(QCTNAME(TP)+" inserts a chalcedony into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"chalcedony");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [red] 'spinel' [in] [into] [the] [indentation]"))
    {
        if (!present("red_spinel",TP))
        {
            NF("You do not have an red spinel!\n");
            return 0;
        }

        gem_string = "There is a red spinel placed in the indentation.";
        gem_heap = present("red_spinel",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the red spinel, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put a red spinel into the indentation.\n");
        say(QCTNAME(TP)+" inserts a red spinel into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"red spinel");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [blue] 'sapphire' [in] [into] [the] [indentation]"))
    {
        if (!present("sapphire",TP))
        {
            NF("You do not have a sapphire!\n");
            return 0;
        }

        gem_string = "There is a sapphire placed in the indentation.";
        gem_heap = present("sapphire",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the sapphire, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put a sapphire into the indentation.\n");
        say(QCTNAME(TP)+" inserts a sapphire into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"sapphire");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [orange-red] 'garnet' [in] [into] [the] [indentation]"))
    {
        if (!present("garnet",TP))
        {
            NF("You do not have any garnets!\n");
            return 0;
        }

        gem_string = "There is a garnet placed in the indentation.";
        gem_heap = present("garnet",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the garnet, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put a garnet into the indentation.\n");
        say(QCTNAME(TP)+" inserts a garnet into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"garnet");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [black] 'diamond' [in] [into] [the] [indentation]"))
    {
        if (!present("black_diamond",TP))
        {
            NF("You do not have any black diamonds!\n");
            return 0;
        }

        gem_string = "There is a black diamond placed in the indentation.";
        gem_heap = present("black_diamond",TP);
        heap_size = gem_heap->num_heap();
        if (heap_size > 1)
        {
            gem_heap->split_heap(heap_size - 1);
            gem = gem_heap->force_heap_split();
        }
        else
            gem = gem_heap;
        gem->move(environment(TP));
        gem->set_no_show_composite(1);
        gem->add_prop(OBJ_M_NO_GET,"You cannot take the black diamond, it "+
            "is being used in a ritual.\n");
        inserted_gem = gem;
        write("You put a black diamond into the indentation.\n");
        say(QCTNAME(TP)+" inserts a black diamond into the indentation.\n");
        TP->add_prop(I_INSERTED_GEM,"black diamond");
        return 1;
    }

    write("You cannot put the "+str+" into the indentation as there are "+
        "rituals that use that type of gem.\n");
    return 1;
}

int
do_place(string str)
{
    object item_heap, item;
    int heap_size;

    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You must be in the pentagram to perform a ritual! <enter pentagram>\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Place what? An item into the pentagram? <place (itemname)>\n");
        return 0;
    }

    if (present("_psuchae_staff_",TP))
    {
        NF("You already have a Staff of Psuchae. You cannot "+
            "create another.\n");
        return 0;
    }

    if (parse_command(str, ({}), 
        "[the] 'cranberry' [in] [into] [the] [pentagram]"))
    {
        if (!herb_present("cranberry",TP))
        {
            NF("You do not have a cranberry!\n");
            return 0;
        }

        pentagram_string = "There is a cranberry placed in the pentagram.";
        item_heap = herb_present("cranberry",TP);
        heap_size = item_heap->num_heap();
        if (heap_size > 1)
        {
            item_heap->split_heap(heap_size - 1);
            item = item_heap->force_heap_split();
        }
        else
            item = item_heap;
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the cranberry, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place a cranberry into the pentagram.\n");
        say(QCTNAME(TP)+" places a cranberry into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"cranberry");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] 'breadroot' [in] [into] [the] [pentagram]"))
    {
        if (!herb_present("breadroot",TP))
        {
            NF("You do not have any breadroot!\n");
            return 0;
        }

        pentagram_string = "There is some breadroot placed in the pentagram.";
        item_heap = herb_present("breadroot",TP);
        heap_size = item_heap->num_heap();
        if (heap_size > 1)
        {
            item_heap->split_heap(heap_size - 1);
            item = item_heap->force_heap_split();
        }
        else
            item = item_heap;
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the breadroot, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place some breadroot into the pentagram.\n");
        say(QCTNAME(TP)+" places some breadroot into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"breadroot");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] 'sargassum' [in] [into] [the] [pentagram]"))
    {
        if (!herb_present("sargassum",TP))
        {
            NF("You do not have any sargassum!\n");
            return 0;
        }

        pentagram_string = "There is some sargassum placed in the pentagram.";
        item_heap = herb_present("sargassum",TP);
        heap_size = item_heap->num_heap();
        if (heap_size > 1)
        {
            item_heap->split_heap(heap_size - 1);
            item = item_heap->force_heap_split();
        }
        else
            item = item_heap;
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the sargassum, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place some sargassum into the pentagram.\n");
        say(QCTNAME(TP)+" places some sargassum into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"sargassum");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] [sea] 'bubble' [in] [into] [the] [pentagram]"))
    {
        if (!herb_present("sea bubble",TP))
        {
            NF("You do not have any sea bubble!\n");
            return 0;
        }

        pentagram_string = "There is some sea bubble placed in the pentagram.";
        item_heap = herb_present("sea bubble",TP);
        heap_size = item_heap->num_heap();
        if (heap_size > 1)
        {
            item_heap->split_heap(heap_size - 1);
            item = item_heap->force_heap_split();
        }
        else
            item = item_heap;
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the sea bubble, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place some sea bubble into the pentagram.\n");
        say(QCTNAME(TP)+" places some sea bubble into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"sea bubble");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] 'heart' [in] [into] [the] [pentagram]"))
    {
        if (!present("heart",TP))
        {
            NF("You do not have any hearts!\n");
            return 0;
        }

        pentagram_string = "There is a heart placed in the pentagram.";
        item_heap = present("heart",TP);
        heap_size = item_heap->num_heap();
        if (heap_size > 1)
        {
            item_heap->split_heap(heap_size - 1);
            item = item_heap->force_heap_split();
        }
        else
            item = item_heap;
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the heart, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place a heart into the pentagram.\n");
        say(QCTNAME(TP)+" places a heart into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"heart");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] 'stick' [in] [into] [the] [pentagram]"))
    {
        if (!present("stick",TP))
        {
            NF("You do not have a stick!\n");
            return 0;
        }

        pentagram_string = "There is a stick placed in the pentagram.";
        item = present("stick",TP);
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the stick, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place a stick into the pentagram.\n");
        say(QCTNAME(TP)+" places a stick into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"stick");
        return 1;
    }

    if (parse_command(str, ({}), 
        "[the] 'staff' [in] [into] [the] [pentagram]"))
    {
        if (!present("staff",TP))
        {
            NF("You do not have a staff!\n");
            return 0;
        }

        item = present("staff",TP);
        if (item->query_prop(OBJ_I_ELEMENTAL_STAFF))
        {
            NF("You cannot use the Elemental Staves for the ritual!\n");
            return 0;
        }

        pentagram_string = "There is a staff placed in the pentagram.";
        item->move(environment(TP));
        item->set_no_show_composite(1);
        item->add_prop(OBJ_M_NO_GET,"You cannot take the staff, it "+
            "is being used in a ritual.\n");
        placed_item = item;
        write("You place a staff into the pentagram.\n");
        say(QCTNAME(TP)+" places a staff into the pentagram.\n");
        TP->add_prop(I_PLACED_ITEM,"staff");
        return 1;
    }

    write("You cannot place the "+str+" into the pentagram as there "+
        "are no rituals that use that type of object.\n");
    return 1;
}

int
do_light(string str)
{
    if (!str)
        return 0;

    if (!parse_command(str, ({}),"[the] 'candles'"))
    {
        NF("Light what? The candles? <light candles>\n");
        return 1;
    }

    if (!TP->query_prop(I_INSERTED_GEM))
    {
        NF("You must insert a gem into the indentation first! <insert "+
           "(gemname)>\n");
        return 0;
    }

    if (!TP->query_prop(I_PLACED_ITEM))
    {
        NF("You must place an item into the pentagram first! <insert "+
           "(itemname)>\n");
        return 0;
    }

    write("You light the candles around the pentagram and the chamber "+
        "becomes a little brighter.\n");
    say(QCTNAME(TP)+" lights the candles around the pentagram and the "+
        "chamber becomes a little brighter.\n");
    candles_string = "The candles are lit.";
    TP->add_prop(I_LIT_THE_CANDLES,1);
    return 1;
}

int
do_enter(string str)
{
    if (TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You are already in the pentagram.\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Enter what? The pentagram? <enter pentagram>\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[the] 'pentagram'"))
    {
        NF("Enter what? The pentagram? <enter pentagram>\n");
        return 0;
    }

    if (in_pent != 0)
    {
        NF("There is already someone in the pentagram.\n");
        return 0;
    }

    if (present("_psuchae_staff_",TP))
    {
        NF("You already have a Staff of Psuchae. You cannot enter "+
            "the pentagram.\n");
        return 0;
    }

    write("You grab the ceremonial robe from the hook, don it, and "+
        "enter the pentagram.\n");
    say(QCTNAME(TP)+" grabs the ceremonial robe from the hook, dons it, "+
        "and enters the pentagram.\n");
    robe_hook = "The hook is empty.";
    TP->add_prop(I_AM_IN_PENTAGRAM,1);
    person_pentagram = capitalize(TP->query_real_name())+" is standing in the pentagram.";
    in_pent = 1;
    return 1;
}

int
do_leave(string str)
{
    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You are not in the pentagram!\n");
        return 0;
    }
    
    if (!str)
    {
        NF("Leave what? The pentagram? <leave pentagram>\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[the] 'pentagram'"))
    {
        NF("Leave what? The pentagram? <leave pentagram>\n");
        return 0;
    }

    if (TP->query_prop(I_INSERTED_GEM))
    {
        NF("You cannot leave the pentagram until you finish the ritual. "+
           "If you must leave, abort the ritual. <abort ritual>\n");
        return 0;
    }

    if (TP->query_prop(I_PLACED_ITEM))
    {
        NF("You cannot leave the pentagram until you finish the ritual. "+
           "If you must leave, abort the ritual. <abort ritual>\n");
        return 0;
    }

    write("You leave the pentagram, remove your ceremonial robe and "+
        "hang it back on the hook.\n");
    say(QCTNAME(TP)+" leaves the pentagram, removes "+TP->query_possessive()+
        " ceremonial robe, and hangs it back on the hook.\n");
    TP->remove_prop(I_AM_IN_PENTAGRAM);
    person_pentagram = "There is nobody in the pentagram.";
    robe_hook = "There is a robe hanging on the hook.";
    in_pent = 0;
    return 1;
}

int
do_abort(string str)
{   
    object gem, gem_name, item, item_name, weapon, weapon_name;

    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You are not in the pentagram!\n");
        return 0;
    }

    if (!str)
    {
        NF("Abort what? The ritual? <abort ritual>\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[the] 'ritual'"))
    {
        NF("Abort what? The ritual? <abort ritual>\n");
        return 0;
    }

    write("You abort the ritual, gathering up your items.\n");
    say(QCTNAME(TP)+" aborts the ritual "+TP->query_pronoun()+
        " was doing.\n");
    
    if (TP->query_prop(I_INSERTED_GEM))
    {
        gem_name = TP->query_prop(I_INSERTED_GEM);
        gem = present(inserted_gem,environment(TP));
        gem->set_no_show_composite(0);
        gem->remove_prop(OBJ_M_NO_GET);
        gem->move(TP,1);
        TP->remove_prop(I_INSERTED_GEM);
        gem_string = "There is nothing in the indentation.";
    }

    if (TP->query_prop(I_PLACED_ITEM))
    {
        item_name = TP->query_prop(I_PLACED_ITEM);
        item = present(placed_item,environment(TP));
        item->set_no_show_composite(0);
        item->remove_prop(OBJ_M_NO_GET);
        item->move(TP,1);
        TP->remove_prop(I_PLACED_ITEM);
        pentagram_string = "There is no item placed in the pentagram.";
    }

    if (TP->query_prop(I_DESIGNATED_WEP))
    {
        weapon_name = TP->query_prop(I_DESIGNATED_WEP);
        weapon = present(designated_weapon,environment(TP));
        weapon->set_no_show_composite(0);
        weapon->remove_prop(OBJ_M_NO_GET);
        weapon->move(TP,1);
        TP->remove_prop(I_DESIGNATED_WEP);
        weapon_string = "";
    }

    if (TP->query_prop(I_LIT_THE_CANDLES))
    {
        TP->remove_prop(I_LIT_THE_CANDLES);
        write("You extinguish the candles and the chamber becomes "+
            "a little bit darker.\n");
        say(QCTNAME(TP)+" extinguishes the candles and the chamber "+
            "becomes a little bit darker.\n");
        candles_string = "The candles are extinguished.";
    }

    TP->remove_prop(I_AM_IN_PENTAGRAM);
    in_pent = 0;
    person_pentagram = "There is nobody in the pentagram.";
    robe_hook = "There is a robe hanging on the hook.";
    write("You leave the pentagram, remove your ceremonial robe and "+
        "hang it back on the hook.\n");
    say(QCTNAME(TP)+" leaves the pentagram, removes "+TP->query_possessive()+
        " ceremonial robe, and hangs it back on the hook.\n");
    return 1;

}

int
do_extinguish()
{
    if (!TP->query_prop(I_AM_IN_PENTAGRAM))
    {
        NF("You are not in the pentagram so you dare not touch anything "+
            "to do with the ritual!\n");
        return 0;
    }

    if (!TP->query_prop(I_LIT_THE_CANDLES))
    {
        NF("The candles are not lit!\n");
        return 0;
    }

    write("Once the ritual candles have been lit, you cannot extinguish "+
        "them. If you wish to abort the ritual, then do so. <abort ritual>\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_create,"create");
    add_action(do_insert,"insert");
    add_action(do_place,"place");
    add_action(do_designate,"designate");
    add_action(do_light,"light");
    add_action(do_extinguish,"extinguish");
    add_action(do_extinguish,"unlight");
    add_action(do_enter,"enter");
    add_action(do_leave,"leave");
    add_action(do_abort,"abort");
}
