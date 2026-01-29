/* 
 *  Wedding Ceremony Book. This object is found in the cabinet in
 *  the sacristry and contains the preparations and instructions
 *  for wedding ceremonies.
 *
 */
inherit "/std/scroll";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <config.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#include "defs.h"
#include SPIRIT_HEADER

#define TRANSFORM_LOG "spirit_circle/wedding_transformation_log"

#define DID_SBRIDE "_did_spirit_wedding_specify_bride"
#define DID_SGROOM "_did_spirit_wedding_specify_groom"
#define DID_TRANS  "_did_spirit_wedding_transform"
#define DID_BEGIN  "_did_spirit_wedding_begin"
#define DID_GWISH  "_did_spirit_wedding_gwish"
#define DID_BWISH  "_did_spirit_wedding_bwish"
#define DID_MARRY  "_did_spirit_wedding_marry"

#define SPIRIT_OBJ    "/d/Calia/guilds/scop/objects/wedding_shadow_obj"
#define PARALYSIS_OBJ "/d/Calia/worshippers/objects/paralyze"
#define LIMIT_OBJECT  "/d/Calia/guilds/scop/objects/limit"
#define MARRIAGE_OBJ  "/d/Emerald/common/marriage/marriage_manager"
#define MARRIAGE_SAVE "/d/Emerald/common/marriage/marriages"

string groom_name;
string bride_name;

void create_scroll()
{
    set_name(({"wedding book","book"}));
    set_short("wedding book");
    add_name(CEREMONIAL_GARB);
    set_long("It is a sacred tome with newly written golden "+
       "lettering. Perhaps you can read or mread it.\n");
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(SPIRIT_OBJECTS+"wedtome.txt");
}

int
specify_bride(string str)
{
    if (!str)
    {
        NF("You must specify the Bride's name.\n");
        return 0;
    }

    if (!present(lower_case(str), environment(TP)))
    {
        NF("The Bride is not present.\n");
        return 0;
    }

    bride_name = capitalize(str);
    
    if (bride_name == groom_name)
    {
        NF("The Bride and Groom cannot have the same name.\n");
        return 0;
    }

    write("Bride is specified as: "+bride_name+".\n");
    TP->add_prop(DID_SBRIDE,1);
    return 1;
}

int
specify_groom(string str)
{
    if (!str)
    {
        NF("You must specify the Groom's name.\n");
        return 0;
    }

    if (!present(lower_case(str), environment(TP)))
    {
        NF("The Groom is not present.\n");
        return 0;
    }

    groom_name = capitalize(str);

    if (bride_name == groom_name)
    {
        NF("The Bride and Groom cannot have the same name.\n");
        return 0;
    }

    write("Groom is specified as: "+groom_name+".\n");
    TP->add_prop(DID_SGROOM,1);
    return 1;
}

int
do_transform()
{
    object bride, groom, shadow_obj;

    if (!TP->query_prop(DID_SBRIDE))
    {
        NF("You have not specified the Bride's name.\n");
        return 0;
    }

    if (!TP->query_prop(DID_SGROOM))
    {
        NF("You have not specified the Groom's name.\n");
        return 0;
    }

    if (!present(INCENSE_CLOUD,environment(TP))) 
    {
        NF("The room should be filled with incense to mark the "+
            "solemnity of such an occassion.\n");
        return 0;
    }

    if (present("_skiamorfi_object_",TP))
    {
        NF("You are already in shadow form. Please revert back to normal "+
           "first.\n");
        return 0;
    }

    bride = present(lower_case(bride_name),environment(TP));
    groom = present(lower_case(groom_name),environment(TP));

    write("You begin the ceremony by drawing a magical pentagram on "+
        "the ground in front of "+capitalize(bride_name)+" and "+
        capitalize(groom_name)+" with your finger. Upon completing "+
        "the drawing, you step inside of it. Concentrating all of your "+
        "energies, you begin the summoning ritual.\n");
    bride->catch_msg(QCTNAME(TP)+" begins by drawing some type of symbol "+
        "on the ground in front of you and "+capitalize(groom_name)+". "+
        "Upon completing the drawing, "+HE+" steps inside of it. "+
        capitalize(HE)+" appears to be in deep concentration.\n");
    groom->catch_msg(QCTNAME(TP)+" begins by drawing some type of symbol "+
        "on the ground in front of you and "+capitalize(bride_name)+". "+
        "Upon completing the drawing, "+HE+" steps inside of it. "+
        capitalize(HE)+" appears to be in deep concentration.\n");
    say(QCTNAME(TP)+" begins by drawing some type of symbol on the "+
        "ground in front of "+capitalize(bride_name)+" and "+
        capitalize(groom_name)+" with "+HIS+" finger. Upon completing "+
        "the drawing, "+HE+" steps inside of it. "+capitalize(HE)+
        "appears to be in deep concentration.\n",({ bride, groom, TP}));
    write("A shadow surrounds your entire body and you feel yourself "+
        "being possessed by Psuchae! Psuchae has been summoned successfully "+
        "to perform this ceremony and speak on your behalf. You feel "+
        "that anything you wanted to say, you could say now. You also "+
        "somehow feel that you cannot move.\n");
    say("Dark shadows begin to rise out of the place on the ground where "+
        QTNAME(TP)+" drew the symbol. They swirl around and around "+HIM+
        ", slowly covering "+HIS+" entire body. "+QCTNAME(TP)+" looks "+
        "entirely different, as if it isn't even "+HIM+" that is standing "+
        "there.\n");
    setuid();
    seteuid(getuid(TO));
    present("_action_limiter_",TP)->remove_object();
    shadow_obj = clone_object(SPIRIT_OBJ);
    shadow_obj->move(TP);
    shadow_obj->start();
    TP->add_prop(DID_TRANS,1);
    log_file(TRANSFORM_LOG, ctime(time())+" Transformation for wedding by "+ 
        TP->query_name() +".\n",-1);
    return 1;
}

int
do_begin()
{
    if (!TP->query_prop(DID_TRANS))
    {
        NF("You have not transformed yet.\n");
        return 0;
    }
    
    write("You say: We have come together here in celebration of the "+
        "joining together of "+capitalize(bride_name)+" and "+
        capitalize(groom_name)+". There are many things to say about "+
        "marriage. Much wisdom concerning the joining together of two "+
        "souls has come our way through all paths of belief, and from many "+
        "cultures. With each union, more knowledge is gained and more "+
        "wisdom gathered. Though we are unable to give all this knowledge "+
        "to these two, who stand before us, we can hope to leave with them "+
        "the knowledge of love and its strengths and the anticipation of "+
        "the wisdom that comes with time. The law of life is love unto all "+
        "beings. Without love, life is nothing, without love, death has "+
        "no redemption. Love is anterior to Life, posterior to Death, "+
        "initial of Creation and the exponent of Earth. If we learn no "+
        "more in life, let it be this. Marriage is a bond to be entered "+
        "into only after considerable thought and reflection. As with any "+
        "aspect of life, it has its cycles, its ups and its downs, its "+
        "trials and its triumphs. With full understanding of this, "+
        capitalize(groom_name)+" and "+capitalize(bride_name)+" have come "+
        "here today to be joined as one in marriage.\nOthers would ask, "+
        "at this time, who gives the bride in marriage, but, as a woman, "+
        "nor a man, is not property to be bought and sold, given and taken, "+
        "I ask simply if she comes of her own will and if she has her "+
        "family's blessing. "+capitalize(bride_name)+", is it true that "+ 
        "you come of your own free will and accord?\n");
    say(QCTNAME(TP)+" whispers in an eerie voice: We have come together "+
        "here in celebration of the joining together of "+
        capitalize(bride_name)+" and "+capitalize(groom_name)+". There "+
        "are many things to say about marriage. Much wisdom concerning the "+
        "joining together of two souls has come our way through all paths "+
        "of belief, and from many cultures. With each union, more knowledge "+
        "is gained and more wisdom gathered. Though we are unable to give "+
        "all this knowledge to these two, who stand before us, we can hope "+
        "to leave with them the knowledge of love and its strengths and the "+
        "anticipation of the wisdom that comes with time. The law of life is "+
        "love unto all beings. Without love, life is nothing, without love, "+
        "death has no redemption. Love is anterior to Life, posterior to "+
        "Death, initial of Creation and the exponent of Earth. If we learn "+
        "no more in life, let it be this. Marriage is a bond to be entered "+
        "into only after considerable thought and reflection. As with any "+
        "aspect of life, it has its cycles, its ups and its downs, its "+
        "trials and its triumphs. With full understanding of this, "+
        capitalize(groom_name)+" and "+capitalize(bride_name)+" have come "+
        "here today to be joined as one in marriage.\nOthers would ask, "+
        "at this time, who gives the bride in marriage, but, as a woman, "+
        "nor a man, is not property to be bought and sold, given and taken, "+
        "I ask simply if she comes of her own will and if she has her "+
        "family's blessing. "+capitalize(bride_name)+", is it true that "+
        "you come of your own free will and accord?\n"); 

    TP->add_prop(DID_BEGIN,1);
    return 1;
}

int
do_gwish()
{
    if (!TP->query_prop(DID_BEGIN))
    {
        NF("You must begin the ceremony first.\n");
        return 0;
    }

    write("You say: Above you are the stars, below you are the stones, "+
        "as time doth pass, remember... Like a stone should your love be "+
        "firm like a star should your love be constant. Let the powers of "+
        "the mind and of the intellect guide you in your marriage, let "+
        "the strength of your wills bind you together, let the power of "+
        "love and desire make you happy, and the strength of your "+
        "dedication make you inseparable. Be close, but not too close. "+
        "Possess one another, yet be understanding. Have patience with "+
        "one another, for storms will come, but they will pass quickly. "+
        "Be free in giving affection and warmth. Have no fear and let "+
        "not the ways of the unenlightened give you unease.\n"+
        capitalize(groom_name)+", I have not the right to bind thee to "+
        capitalize(bride_name)+", only you have this right. If it be "+
        "your wish, say so at this time and place your ring in her hand.\n");
    say(QCTNAME(TP)+" whispers in an eerie voice: Above you are the stars, "+
        "below you are the stones, as time doth pass, remember... Like a "+
        "stone should your love be firm like a star should your love be "+
        "constant. Let the powers of the mind and of the intellect guide "+
        "you in your marriage, let the strength of your wills bind you "+
        "together, let the power of love and desire make you happy, and "+
        "the strength of your dedication make you inseparable. Be close, "+
        "but not too close. Possess one another, yet be understanding. "+
        "Have patience with one another, for storms will come, but they "+
        "will pass quickly. Be free in giving affection and warmth. "+
        "Have no fear and let not the ways of the unenlightened give "+
        "you unease.\n"+capitalize(groom_name)+", I have not the right "+
        "to bind thee to "+capitalize(bride_name)+", only you have this "+
        "right. If it be your wish, say so at this time and place your "+
        "ring in her hand.\n");
    
    TP->add_prop(DID_GWISH,1);
    return 1;
}

int
do_bwish()
{
    if (!TP->query_prop(DID_GWISH))
    {
        NF("You must do the groom-wish first.\n");
        return 0;
    }

    write("You say: "+capitalize(bride_name)+", I have not the right "+
        "to bind thee to "+capitalize(groom_name)+", only you have this "+
        "right. If it be your wish, say so at this time and place your "+
        "ring in his hand.\n");
    say(QCTNAME(TP)+" whispers in an eerie voice: "+capitalize(bride_name)+", I have not the right "+
        "to bind thee to "+capitalize(groom_name)+", only you have this "+
        "right. If it be your wish, say so at this time and place your "+
        "ring in his hand.\n");

    TP->add_prop(DID_BWISH,1);
    return 1;
}

int
do_marry(string str)
{
    string who1, who2, material;
    int ret;

    if (!TP->query_prop(DID_BWISH))
    {
        NF("You must do the bride-wish first.\n");
        return 0;
    }

    if (!str)
    {
        NF("You must specify the metal type of the wedding bands.\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w [and] %w %w", who1, who2, material))
    {
        NF("Proper syntax is 'marry <player> and <player> <band material>'.\n");
        return 0;
    }

    who1 = lower_case(who1);
    who2 = lower_case(who2);
    material = lower_case(material);
    /*
    setuid();
    seteduid(getuid(MARRIAGE_OBJ));
    if ((ret = (MARRIAGE_OBJ->wed(who1, who2, material))) == 1)
    {
        write(capitalize(who1) + " is already married!\n");
        return 1;
    }
   
    if (ret == 2)
    {
        write(capitalize(who2) + " is already married!\n");
        return 1;
    }

    setuid();
    seteduid(getuid(MARRIAGE_OBJ));
    log_file(MARRIAGE_LOG, capitalize(TP->query_real_name()) +
        "did the wedding in the temple in Calia.\n");
    */
    write("The wedding is completed. You should 'revert' now.\n");
    TP->add_prop(DID_MARRY,1);
    return 1;
}

int
do_revert()
{
    present("_skiamorfi_object_",TP)->dispel_spell_effect();
    setuid();
    seteuid(getuid(TO));
    clone_object(LIMIT_OBJECT)->move(TP);
    TP->remove_prop(DID_SBRIDE);
    TP->remove_prop(DID_SGROOM);
    TP->remove_prop(DID_TRANS);
    TP->remove_prop(DID_BEGIN);
    TP->remove_prop(DID_GWISH);
    TP->remove_prop(DID_BWISH);
    TP->remove_prop(DID_MARRY);
    log_file(TRANSFORM_LOG, ctime(time())+" Transformation back for wedding by "+ 
        TP->query_name() +".\n",-1);
    return 1;
}

void
init()
{
    ::init();
    add_action(specify_bride,"bride");
    add_action(specify_groom,"groom");
    add_action(do_begin,"begin");
    add_action(do_transform,"transform");
    add_action(do_gwish,"groom-wish");
    add_action(do_bwish,"bride-wish");
    add_action(do_marry,"marry");
    add_action(do_revert,"revert");
}
