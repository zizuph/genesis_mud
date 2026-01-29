
/*
 * garden.c
 *
 * Garden for the Spirit Circle of Psuchae Temple
 * New members to the guild will be teleported here after being
 * initiated. They can also teleport to here with the Anakalo
 * Gift. 
 *
 * Copyright (C): Jaacar (Mike Phipps), July 30th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#define ELEMENTALIST_TEMPLE "/d/Calia/guilds/elementalists/temple/"

void
create_room()
{
    set_short("Garden");
    set_long("You are standing in the holy garden of Psuchae. Here "+
        "you see an amazing variety of plants, trees and flowers "+
        "growing all around you. A small path naturally curves its "+
        "way in here from the east and then forms a perfect circle "+
        "around the five obelisks in the centre of the garden. You "+
        "feel an inner peace just being in this place of magnificence "+
        "and beauty.\n");

    add_item("stones", "The stones are small white river stones, which "+
      "are covered in moss. On one stone however, the moss has been "+
      "pulled away, and you can make out black veins of color in it.\n");
    add_item("veins", "Closer examination of the veins shows that they "+
      "are etchings, masterfully designed to read:\nYou have set the "+
      "powers of the four quarters of the earth to cross each other.  "+
      "You have made me cross the good road and the road of difficulties, "+
      "and where they cross, the place is holy. Day in, day out, "+
      "forevermore, You are the life of things.\n");    
    add_item(({"first obelisk","1st obelisk","black obelisk"}),
        "At the northern most point lies the first obelisk. This "+
        "black stone obelisk represents Psuchae. In a hole on "+
        "the top of the obelisk is a staff.\n");
    add_item(({"second obelisk","2nd obelisk","white obelisk"}), 
        "In the northwestern corner lies the second obelisk. This "+
        "white stone obelisk represents Lady Aeria. In a hole on "+
        "the top of the obelisk is a staff.\n");
    add_item(({"third obelisk","3rd obelisk","blue obelisk"}), 
        "In the northeastern corner lies the third obelisk. This "+
        "blue stone obelisk represents Lord Diabrecho. In a hole on "+
        "the top of the obelisk is a staff.\n");
    add_item(({"fourth obelisk","4th obelisk","brown obelisk"}), 
        "In the southwestern corner lies the fourth obelisk. This "+
        "brown stone obelisk represents Lady Gu. In a hole on "+
        "the top of the obelisk is a staff.\n");
    add_item(({"fifth obelisk","5th obelisk","red obelisk"}), 
        "In the southeastern corner lies the fifth obelisk. This "+
        "red stone obelisk represents Lord Pyros. In a hole on "+
        "the top of the obelisk is a staff.\n");
    add_item("staff","In a hole in the top of each obelisk lies "+
        "a staff, replicas of the ones you constructed to join "+
        "the Circle. Try as you might, you cannot take them.\n");
    add_item("pentagram","The obelisks and black lines form the "+
        "pattern of a pentagram in the centre of the garden.\n");
    add_item(({"lines","black lines"}),"The black lines of dirt "+
        "and ground connect the obelisks together forming a "+
        "pentagram.\n");
    add_item(({"obelisk","obelisks","five obelisks"}),"In the "+
        "centre of the path you see five obelisks. The ground is "+
        "dug up in straight lines between the obelisks forming "+
        "black lines. Each of the obelisks is made of a different "+
        "coloured stone and stands about five feet high. They look "+
        "very smooth to the touch.\n");
    add_item(({"circle","perfect circle"}),"The path forms a "+
        "perfect circle around the five obelisks, then winds "+
        "its way back to the east.\n");
    add_item(({"flower","flowers"}),"There must be at least five "+
        "hundred flowers here of every size, shape and colour "+
        "imaginable. Amoung the plants you recognize are the pansy, "+
        "the iris, the hydrangea, orchids, and the hanwi.\n");
    add_item("hanwi","Also known as wildflowers, they are an "+
        "extremely delicate white flower with four large white "+
        "petals and a much thinner and more delicate petal that "+
        "sits just behind and inbetween the larger four petals. "+
        "The white gives way to gradually darker shades of green "+
        "the closer the petal is to the stamen. They grow very "+
        "close to the ground.\n");
    add_item(({"grass","lush grass","lush grassy area"}),"The grass "+
        "is all a uniform height and looks like a perfect green "+
        "carpet covering the area. Throughout the grass are pockets "+
        "of flowers.\n");
    add_item(({"path","dirt path","small dirt path","small path"}),
        "The small path consists of reddish crushed gravel and dirt, "+
        "and it winds its way naturally off to east and forms a perfect "+
        "circle around the five obelisks.\n");
    add_item(({"plant","plants"}),"There are several types of "+
        "plants growing in this place including trees and "+
        "flowers.\n");
    add_item(({"tree","trees"}),"There are several types of trees "+
        "growing here. Of all of them that you see, you recognize "+
        "pine trees, bonsai trees and gardenia trees.\n");
    add_item(({"pine tree","pine trees"}),"These beautiful tall "+
        "pine trees, also known as evergreen trees are almost "+
        "perfectly triangular in shape. They are a deep forest "+
        "green in colour and very soft to the touch. They grow "+
        "around alot of the plants here.\n");
    add_item("pansy","The pansy orchid has large, flat blooms. "+
        "Their flowers are burgandy in colour and have an outer "+
        "edge of white with a yellow throat. Their leaves are "+
        "slender and pointed, much like an iris. The flowers have "+
        "only a few petals and are splayed out, almost looking a bit "+
        "like fingers on top with larger petals on the lower half "+
        "resembling the palm of a hand.\n");
    add_item("iris","There are irises of both blue and purple in "+
        "colour, all of them with a yellow centre, long pointed "+
        "leaves, and blooms that appear to have burst from the stem.\n");
    add_item(({"gardenia tree","gardenia trees","gardenia"}),"This small "+
        "flowering tree has large white blooms and large, oval "+
        "waxy leaves. These trees are very delicate and appear "+
        "as though someone has taken a bunch of fallen flower "+
        "petals and spread them out in a flat circle and called "+
        "it a plant. They vary in size from a hands height tall "+
        "to almost two hands height.\n");
    add_item(({"bonsai tree","bonsai trees","bonsai"}),"These diminutive "+
        "trees have a small twisting leaning trunk and branches "+
        "and tiny leaves. Each diminutive tree represents nature "+
        "in concentrated form, and no two trees are alike. They "+
        "appear to have been shaped by the currents. They are "+
        "about one and a half hands high, and have a wide, triangular "+
        "head of foliage and exaggerated width to heighth proportion. "+
        "They are surrounded by mossy stones.\n");
    add_item(({"mossy stones","mossy stone"}),"These small stones "+
        "are covered in some strange moss and surround the bonsai "+
        "trees.\n");
    add_item(({"strange moss","moss"}),"The moss is brownish-red in "+
        "colour and very strange to the touch.\n");
    add_item("hydrangea","These flowers are large, coloured blue, "+
        "and almost dome-shaped, the flat being where the stem meets "+
        "the bloom. They look as if someone has come along and pinched "+
        "merangue or frosting into a random pattern with the petals. "+
        "The leaves are your standard oval with a point shape, "+
        "slightly fuzzy, and have deep lines radiating from the centre "+
        "of the leaf to its outer edges.\n");
    add_item(({"orchid","orchids"}),"These orchids, known also as snowfrost "+
        "phalaenopsis, have the typical orchid long, broad, waxy "+
        "leaves at the base and a tall spindly stem that offers "+
        "the heavy blossoms at the top of it, all in a row. They "+
        "are light pink with a dark pink stamen and frosted outer "+
        "rims, hence the name.\n");

    OUT;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"pathway","east",0,1);
}

int
do_smell(string str)
{
    if (!str)
    {
        write("You exhale deeply then breathe in a large breath "+
            "through your nose to take in the various smells around "+
            "you. It is almost overpowering, the mixture of all of "+
            "the different flowers and trees is intoxicating. You "+
            "almost pass out from the smell.\n");
        say(QCTNAME(TP)+" takes in a large breath through "+HIS+
            " nose and looks like "+HE+" is almost ready to pass out "+
            "from the intoxicating smell of the flowers and trees here.\n");
        return 1;
    }

    if (str == "flowers")
    {
        NF("Which flowers would you like to smell? The pansy, "+
            "the iris, the hydrangea, the orchids, or the hanwi? "+
            "<smell pansy> <smell iris> <smell hydrangea> <smell orchid> "+
            "<smell hanwi>\n");
        return 0;
    }

    if (str == "trees")
    {
        NF("Which trees would you like to smell? The pines, the "+
            "bonsai, or the gardenia? <smell pine> <smell bonsai> "+
            "<smell gardenia>\n");
        return 0;
    }

    if (str == "pansy")
    {
        write("You bend over to smell the pansy. It smells faintly "+
            "sweet and slightly dusty.\n");
        say(QCTNAME(TP)+" bends over and smells a pansy.\n");
        return 1;
    }

    if (str == "iris")
    {
        write("You bend over to smell the iris. It gives a soft, "+
            "pleasing scent.\n");
        say(QCTNAME(TP)+" bends over and smells an iris.\n");
        return 1;
    }

    if (str == "hydrangea")
    {
        write("You bend over to smell the hydrangea. It has a "+
            "subdued honeyed scent.\n");
        say(QCTNAME(TP)+" bends over and smells a hydrangea.\n");
        return 1;
    }

    if (str == "orchid")
    {
        write("You bend over to smell the orchid. It has a lavish, "+
            "musky odor.\n");
        say(QCTNAME(TP)+" bends over and smells an orchid.\n");
        return 1;
    }

    if (str == "hanwi")
    {
        write("You bend over to smell the hanwi. It has a faint, "+
            "delicately spicy odor.\n");
        say(QCTNAME(TP)+" bends over and smells a hanwi.\n");
        return 1;
    }

    if (str == "pine")
    {
        write("You bend over to smell the pine tree. It has a "+
            "heavy sharp scent.\n");
        say(QCTNAME(TP)+" bends over and smells a pine tree.\n");
        return 1;
    }

    if (str == "bonsai")
    {
        write("You bend over to smell the bonsai tree. It smells "+
            "of the earth.\n");
        say(QCTNAME(TP)+" bends over and smells a bonsai tree.\n");
        return 1;
    }

    if (str == "gardenia")
    {
        write("You bend over to smell the gardenia tree. It has a "+
            "strong but suprisingly delicate scent.\n");
        say(QCTNAME(TP)+" bends over and smells a gardenia tree.\n");
        return 1;
    }

    NF("What do you want to smell? The flowers? The trees?\n");
    return 0;
}

int
do_pick(string str)
{
    if (!str)
    {
        NF("Pick what?\n");
        return 0;
    }
    
    if (str == "flower")
    {
        write("You dare not pick any of the flowers!\n");
        say(QCTNAME(TP)+" bends over to pick a flower, but decides against "+
            "it at the very last moment.\n");
        return 1;
    }

    if (str == "flowers")
    {
        write("You dare not pick any of the flowers!\n");
        say(QCTNAME(TP)+" bends over to pick a flower, but decides against "+
            "it at the very last moment.\n");
        return 1;
    }

    if (str == "nose")
    {
        write("Gross!\n");
        say(QCTNAME(TP)+" picks "+HIS+" nose.\n");
        TP->add_prop(LIVE_S_SOULEXTRA,("picking "+HIS+" nose"));
        return 1;
    }

    NF("Pick what?\n");
    return 0;
}

int
do_touch(string str)
{
    if (!str)
        return 0;

    if (str == "obelisk")
    {
        NF("Which obelisk would you like to touch? <touch black obelisk> "+
            "<touch white obelisk> <touch blue obelisk> <touch brown obelisk> "+
            "<touch red obelisk>\n");
        return 0;
    }

    if (str == "black obelisk")
    {
        if (TP->test_bit("Calia",SCOP_GURU_GROUP,SCOP_GURU_BIT))
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the black obelisk. You feel the powers of Psuchae flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the black obelisk "+
                "briefly.\n");
            return 1;
        }

        if (COUNCIL_CODE->is_spirit_apprentice(TP->query_real_name()))
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the black obelisk. You feel the powers of Psuchae flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the black obelisk "+
                "briefly.\n");
            return 1;
        }
        else
        {
            if (!present("_skiamorfi_object_",TP))
            {
                write("You reach your hand out and run it across the smoothness "+
                    "of the black obelisk. You feel the powers of Psuchae "+
                    "flowing throughout your body, the energy coursing through "+
                    "your veins. As you pull your hand away you feel as if "+
                    "your very soul is being pulled into the obelisk. You "+
                    "hear a voice ringing in your mind yelling \"Help! Help "+
                    "me now!\".\nYou quickly pull your hand away.\n");
                say(QCTNAME(TP)+" runs "+HIS+" hand across the black obelisk "+
                    "briefly then quickly jerks it back to "+HIS+" side.\n");
                return 1;
            }

            write("You reach your shadowy hand out and run it across the "+
                "smoothness of the black obelisk. Your body races with "+
                "energy and you feel a presence within the obelisk. You "+
                "hear a voice ringing in your mind yelling \"Help! Help "+
                "me now!\". You look down to see that your hand has actually "+
                "passed inside of the obelisk. You quickly pull your hand "+
                "back and see that the shadowy hand is unharmed. You know "+
                "in your mind that you could enter the obelisk if you "+
                "wished to do so.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hand across the black obelisk "+
                "briefly. Perhaps you are imagining it, but it appears "+
                "as if "+HIS+" hand is actually passing through the surface "+
                "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
                "hand back from the obelisk.\n");
            return 1;
        }
    }

    if (str == "white obelisk")
    {
        if (TP->query_skill(SS_PATRON_ELEMENTAL) == AIR_FLAG)
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the black obelisk. You feel the powers of Lady Aeria flowing "+
                "throughout your body, her energies coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
                "briefly.\n");
            return 1;
        }
        write("You reach your hand out and run it across the smoothness of "+
            "the white obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
            "briefly.\n");
        return 1;
    }

    if (str == "blue obelisk")
    {
        if (TP->query_skill(SS_PATRON_ELEMENTAL) == WATER_FLAG)
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the blue obelisk. You feel the powers of Lord Diabrecho "+
                "flowing throughout your body, his energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the blue obelisk "+
                "briefly.\n");
            return 1;
        }
        write("You reach your hand out and run it across the smoothness of "+
            "the blue obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the blue obelisk "+
            "briefly.\n");
        return 1;
    }

    if (str == "brown obelisk")
    {
        if (TP->query_skill(SS_PATRON_ELEMENTAL) == EARTH_FLAG)
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the brown obelisk. You feel the powers of Lady Gu "+
                "flowing throughout your body, her energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the brown obelisk "+
                "briefly.\n");
            return 1;
        }
        write("You reach your hand out and run it across the smoothness of "+
            "the brown obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the brown obelisk "+
            "briefly.\n");
        return 1;
    }

    if (str == "red obelisk")
    {
        if (TP->query_skill(SS_PATRON_ELEMENTAL) == FIRE_FLAG)
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the red obelisk. You feel the powers of Lord Pyros "+
                "flowing throughout your body, his energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the red obelisk "+
                "briefly.\n");
            return 1;
        }
        write("You reach your hand out and run it across the smoothness of "+
            "the red obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the red obelisk "+
            "briefly.\n");
        return 1;
    }
    
    NF("Which obelisk would you like to touch? <touch black obelisk> "+
        "<touch white obelisk> <touch blue obelisk> <touch brown obelisk> "+
        "<touch red obelisk>\n");
    return 0;
}

int
do_enter(string str)
{
    if (str != "black obelisk")
    {
        NF("Enter what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        NF("What?\n");
        return 0;
    }

    if (COUNCIL_CODE->is_spirit_apprentice(TP->query_real_name()))
    {
        NF("What?\n");
        return 0;
    }

    if (TP->test_bit("Calia",SCOP_GURU_GROUP,SCOP_GURU_BIT))
    {
        write("You cannot seem to enter the obelisk anymore.\n");
        return 1;
    }

    if (!present("_skiamorfi_object_",TP))
    {
        write("You boldy step forth and solidly walk into the "+
            "black obelisk, your body falling to the ground with a "+
            "loud 'thud' sound. You feel a bit dizzy and very "+
            "embarrased.\n");
        say(QCTNAME(TP)+" boldy steps forward and walks right into "+
            "the black obelisk, "+HIS+" body falling backwards to the "+
            "ground with a loud 'thud' sound. "+capitalize(HE)+" stands "+
            "up, looking a little dizzy and quite embarrased.\n");
        TP->command("blush");
        return 1;
    }

    write("You boldy step forth and walk right though the side of the "+
        "black obelisk. You suddenly find yourself elsewhere.\n");
    say(QCTNAME(TP)+" boldy steps foward and walks right through the side "+
        "of the black obelisk, disappearing from your sight.\n");
    TP->move_living("X",SPIRIT_TEMPLE+"obelisk_entrance");
    tell_room(environment(TP),QCTNAME(TP)+" arrives from outside of the "+
        "obelisk.\n",TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_smell,"smell");
    add_action(do_pick,"pick");
    add_action(do_touch,"touch");
    add_action(do_enter,"enter");
}
                                                      
