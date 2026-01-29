
/*
 * pathway.c
 *
 * Pathway for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#define DID_EXAMINE_WATER "_did_examine_the_water"
void
create_room()
{
    set_short("Pathway");
    set_long("You are wandering down a small dirt path in a lush "+
        "grassy area. On both sides of the path are flowers of "+
        "every size, shape and colour imaginable. The smell from "+
        "the flowers almost makes you lose conciousness it is so "+
        "beautiful. In the centre of the path there is a fountain. "+
        "East from here you see the temple, somewhat "+
        "camouflaged by the trees surrounding it and the vines "+
        "growing up the sides of it. Off to the west you can see "+
        "a large round garden with some large objects in it.\n");

    add_item("fountain","There is a magnificent fountain here in "+
        "the middle of the path. It is made of a bright blue stone "+
        "and has a statue of a lady holding her hands up in prayer "+
        "in the centre. The water flows from the top of her hands, "+
        "down around her body and falls into the large basin at the "+
        "bottom of the fountain.\n");
    add_item("statue","The statue in the fountain is of a lady holding "+
        "her hands up in prayer.\n");
    add_item("water","@@examine_water@@");
    add_item(({"basin","large basin"}),"The large basin at the bottom "+
        "of the fountain holds all of the water that falls from around "+
        "the statue in the centre of the fountain. Water splashes all "+
        "around as it falls from above into the basin.\n");
    add_item(({"objects","large objects"}),"The large objects appear "+
        "from this point to be some type of monoliths or obelisks of "+
        "some type. You will have to go west to look at them in any "+
        "more detail.\n");
    add_item(({"garden","round garden","large garden","large round garden"}),
        "To the west you see a large round garden with some large objects "+
        "in it. You would have to go west to make out any more details.\n");
    add_item("temple","The temple lies off to the east. Vines "+
        "crawl their way up the outside of it giving it a sort "+
        "of natural camouflage.\n");
    add_item(({"vine","vines"}),"The vines are dark green in colour "+
        "and seem to crawl their way up the outside of the temple.\n");
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
        "of flowers. Meandering through the middle of the area is "+
        "a small dirt path.\n");
    add_item(({"path","dirt path","small dirt path","small path"}),
        "The small path consists of reddish crushed gravel and dirt, "+
        "and it winds its way naturally off to the garden to the west "+
        "and back to the temple to the east. On both sides of the "+
        "path are flowers.\n");
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
        "around alot of the plants here and add a natural barrier "+
        "from the outside world to the temple located to the east.\n");
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
    set_tell_time(60);
    add_tell("The sound of the water running in the fountain is soothing "+
        "to your soul.\n");
    add_tell("You hear the water bubbling and splashing from the fountain.\n");
    add_tell("A bit of water splashes your feet from the fountain.\n");
    add_tell("A small bird flies up to the statue, takes a quick drink, "+
        "then flies away again.\n");

    OUT;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"garden","west",0,1);
    add_exit(SPIRIT_TEMPLE+"vestibule","east",0,1);
}

string
examine_water()
{
    if (TP->query_prop(DID_EXAMINE_WATER))
        return "The water flows from the hands at the top of the "+
          "statue, down around the body of the statue, and into the basin "+
          "at the bottom for the fountain. As you watch the play of "+
          "light on the water, you perceive there may be words in the light.\n"+
          "You close your eyes briefly, and when you reopen them, the words "+
          "are clear...\n\n"+
          "Great Spirit, Great Spirit,\n"+
          "all over the Earth the faces of living things are all alike.\n"+
          "With tenderness have these come up out of the ground.\n"+
          "Look upon these faces of children without number\n"+
          "and with children in their arms\n"+
          "that they may face the winds\n"+
          "and walk the good road to the day of quiet.\n";
    
    TP->add_prop(DID_EXAMINE_WATER, 1);
    return "The water flows from the hands at the top of the "+
        "statue, down around the body of the statue, and into the basin "+
        "at the bottom for the fountain. As you watch the play of "+
        "light on the water, you perceive there may be words in the light.\n";
           
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
do_drink(string str)
{
    string x, y, z;
    int c;

    if (!str)
        return 0;

    if ((sscanf(str,"%sfrom %s",x,y)) != 2)
        return 0;
    
    if (!(x == "" || x == "water "))
        return 0;
  
    if (sscanf(y, "the %s", z))
    {
        y = z;
    }
 
    if (y != "fountain")
        return 0;
    
    c = 0;
  
    while (TP->drink_soft(50, 0) && c < 15) c++;
  
    if (!c)
    {
        write("You have drunk all that you can.\n");
        return 1;
    }
 
    write("You drink some water from the fountain.\n");
    say(QCTNAME(TP) + " drinks some water from the fountain.\n");
    return 1;
}

int
do_splash()
{
    write("You splash your hands in the fountain.\n");
    say(QCTNAME(TP)+" splashes "+HIS+" hands in the fountain.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_smell,"smell");
    add_action(do_pick,"pick");
    add_action(do_splash,"splash");
    add_action(do_drink,"drink");
}
