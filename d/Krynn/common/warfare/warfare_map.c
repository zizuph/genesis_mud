/*
 *  Inherit this in to a room you want to leverage the exa_warmap
 *  ascii map function.
 *
 *  Arman - June 2018
 */


#include "/d/Krynn/common/warfare/warfare.h" 

string icewall = "        "; // Icewall area
string est = "        "; // Estwilde area
string na = "  ";   // North Abanasinia
string ca = "  ";   // Central Abanasinia
string sa = "  ";   // Solace area
string np = "  ";   // Newports area
string nl = "    "; // Nightlund area
string tt = "    "; // Throtyl Pass area
string gl = "    "; // Guardlund area
string wp = "        "; // WSP area

string
exa_warmap()
{
    if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == WHITE_ARMY)
        icewall = "!W!W!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == RED_ARMY)
        icewall = "!R!R!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == BLUE_ARMY)
        icewall = "!B!B!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == BLACK_ARMY)
        icewall = "!b!b!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == GREEN_ARMY)
        icewall = "!G!G!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == NEIDAR_ARMY)
        icewall = "$D$D$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == KNIGHT_ARMY)
        icewall = "#K#K#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ICEWALL) == FREE_ARMY)
        icewall = "        ";

    if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == WHITE_ARMY)
        est = "!W!W!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == RED_ARMY)
        est = "!R!R!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == BLUE_ARMY)
        est = "!B!B!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == BLACK_ARMY)
        est = "!b!b!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == GREEN_ARMY)
        est = "!G!G!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == NEIDAR_ARMY)
        est = "$D$D$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == KNIGHT_ARMY)
        est = "#K#K#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_ESTWILDE) == FREE_ARMY)
        est = "        ";

    if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == WHITE_ARMY)
        na = "!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == RED_ARMY)
        na = "!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == BLUE_ARMY)
        na = "!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == BLACK_ARMY)
        na = "!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == GREEN_ARMY)
        na = "!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == NEIDAR_ARMY)
        na = "$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == KNIGHT_ARMY)
        na = "#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NORTH_ABANASINIA) == FREE_ARMY)
        na = "  ";

    if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == WHITE_ARMY)
        ca = "!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == RED_ARMY)
        ca = "!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == BLUE_ARMY)
        ca = "!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == BLACK_ARMY)
        ca = "!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == GREEN_ARMY)
        ca = "!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == NEIDAR_ARMY)
        ca = "$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == KNIGHT_ARMY)
        ca = "#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_CENTRAL_ABANASINIA) == FREE_ARMY)
        ca = "  ";

    if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == WHITE_ARMY)
        sa = "!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == RED_ARMY)
        sa = "!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == BLUE_ARMY)
        sa = "!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == BLACK_ARMY)
        sa = "!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == GREEN_ARMY)
        sa = "!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == NEIDAR_ARMY)
        sa = "$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == KNIGHT_ARMY)
        sa = "#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_SOLACE) == FREE_ARMY)
        sa = "  ";

    if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == WHITE_ARMY)
        np = "!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == RED_ARMY)
        np = "!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == BLUE_ARMY)
        np = "!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == BLACK_ARMY)
        np = "!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == GREEN_ARMY)
        np = "!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == NEIDAR_ARMY)
        np = "$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == KNIGHT_ARMY)
        np = "#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == FREE_ARMY)
        np = "  ";

    if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == WHITE_ARMY)
        nl = "!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == RED_ARMY)
        nl = "!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == BLUE_ARMY)
        nl = "!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == BLACK_ARMY)
        nl = "!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == GREEN_ARMY)
        nl = "!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == NEIDAR_ARMY)
        nl = "$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == KNIGHT_ARMY)
        nl = "#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_NIGHLUND) == FREE_ARMY)
        nl = "    ";

    if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == WHITE_ARMY)
        tt = "!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == RED_ARMY)
        tt = "!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == BLUE_ARMY)
        tt = "!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == BLACK_ARMY)
        tt = "!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == GREEN_ARMY)
        tt = "!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == NEIDAR_ARMY)
        tt = "$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == KNIGHT_ARMY)
        tt = "#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_THROTYL) == FREE_ARMY)
        tt = "    ";

    if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == WHITE_ARMY)
        gl = "!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == RED_ARMY)
        gl = "!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == BLUE_ARMY)
        gl = "!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == BLACK_ARMY)
        gl = "!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == GREEN_ARMY)
        gl = "!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == NEIDAR_ARMY)
        gl = "$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == KNIGHT_ARMY)
        gl = "#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_GUARDLUND) == FREE_ARMY)
        gl = "    ";
   
    if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == WHITE_ARMY)
        wp = "!W!W!W!W";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == RED_ARMY)
        wp = "!R!R!R!R";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == BLUE_ARMY)
        wp = "!B!B!B!B";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == BLACK_ARMY)
        wp = "!b!b!b!b";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == GREEN_ARMY)
        wp = "!G!G!G!G";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == NEIDAR_ARMY)
        wp = "$D$D$D$D";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == KNIGHT_ARMY)
        wp = "#K#K#K#K";
    else if(ARMYMASTER->army_in_area(WAR_AREA_WESTSOL) == FREE_ARMY)
        wp = "        ";


    return "\n" +
        "==============================================================================\n"+
        "      __            __   /                          \\ \n"+
        "     /  \\      __--/  \\_/   "+wp+"        "+nl+nl+" \\      | \n"+
        "     \\   \\    |    ^   "+wp+wp+"      "+nl+nl+" |    /  \n"+
        "      `,  |  /   ^   "+wp+wp+"        ~~~~    _/    / \n"+
        "      _-` [P]   ^                       ~ ~~"+nl+" [] Kalaman  \n"+
        "     |   ^ ^ ^ ^      Vingaard Keep  ~~ "+nl+nl+"   `---`       "+est+"\n"+
        "     |    ^  "+wp+"     []    ~~~ ~ "+nl+nl+"  ^     "+est+est+"\n"+
        "      \\  ^      ~~~     ~  ~~~ "+gl+" ~~ "+nl+nl+" ^    "+est+est+"\n"+
        "       | ^  "+wp+" ~~~       "+gl+gl+" ~~ "+nl+" ^     \n"+
        "       |        ~~~ "+wp+"    "+gl+gl+"  ~  "+nl+" ^     [] Iron Delving \n"+
        "        |    ~   "+wp+"     "+gl+gl+"     ~ "+tt+"  ^ ^\n"+
        "         |    "+wp+"   @@@  "+gl+gl+"   "+tt+tt+"   ^ ^ ^ ^ ^ ^   ^ ^\n"+
        "     |\\__|  "+wp+"   @_--__-, "+gl+"  "+tt+tt+"  ^ ^   __  ^ ^ ^ ^ \n"+  
        "     |_  ,____        @/       `--,   "+tt+tt+"  _--__/   [] Sanction \n"+
        "       `-     `----___/            \\______     /          / \n"+
        "                          |\\_            `,__/    _---__/   ^ ^ ^ ^ \n"+
        "               __--__     |   \\                   / \n"+
        "       __,--,_/  "+na+na+" \\   |   |                  /   \n"+
        "       \\     ^  "+na+na+" ^ \\   \\  |       ____      |    #K = Knight forces\n"+
        "     __,   ^"+sa+" "+na+na+na+" ^ |   \\/       /     \\     \\   !* = Dragonarmy forces\n"+
        "    /   ^   [s]"+sa+sa+ca+"^ |            /       \\     |  $D = Neidar forces \n"+
        "    |    ^  "+sa+sa+ca+ca+ca+"|            |        |     | \n"+
        "     \\  @@@  "+np+np+np+np+" \\            |         \\    \\ \n"+
        "    _/   @@@@"+np+np+" []___,           ,          \\    \\ \n"+
        "   /   @@@@ "+np+np+"   \\New Ports     __\\          \\___\\ \n"+
        "  /  @@@@@ ^ []  ^  \\            / \n"+
        " /       Pax Tharkas \\          /      -=  BATTLEFIELD MAP OF  =-\n"+
        "  \\      ^  ^ ^  ^    \\________/       -= THE WAR OF THE LANCE =-\n"+
        "    \\_____     ^^ ^             \n"+
        "          \\--__ ^^^                       "+icewall+icewall+"\n"+
        "               |  ^      [] Tarsis   "+icewall+icewall+icewall+"\n" +
        "      --------/ "+icewall+"            "+icewall+icewall+icewall+icewall+" \n" +
        "     /   "+icewall+icewall+icewall+icewall+icewall+icewall+icewall+icewall+"\n" +
        "==============================================================================\n"+
        "";
}

