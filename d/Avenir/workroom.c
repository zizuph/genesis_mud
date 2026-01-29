//-*-C++-*-
// updated by Ilyian, 10 April. Added exits.

inherit "/std/room";

public void
create_room(void)
{
    set_short("This is Avenir's workroom");
    set_long("This is Avenir's workroom.  Ornately furnished"+
      " and lavishly decorated, it looks like it was plucked"+
      " straight from a High Lord's palace.\n  "+
      " From the vaulted ceiling hang several chandeliers"+
      " whose light casts an unearthly, cool glow upon the"+
      " mirrored floor.  Paintings and sculptures of fanciful"+
      " creatures line the walls, inviting meditative contem"+
      "plation.  Three carnelian thrones, heavily carved and"+
      " set with multi-coloured gemstones, provide the only"+
      " seating.  A reverent hush lays over the room, one"+
      " which Faithful and Infidels alike are reluctant to"+
      " disturb.\n");

    add_item(({"ceiling", "chandelier", "chandeliers", "source",
	"prism", "pieces"}),
      "The vaulted ceiling is painted with odd swirling shapes."+
      "  From it are hanging chandeliers using prism-cut pieces"+
      " of the Source for illumination, rather than candles. "+
      " Such a display of wealth is awe-inspiring.\n");

    add_item(({"mirror", "mirrors", "floor", "mirrored floor"}),
      "The cool light of the chandeliers reflects off of the"+
      " mirrored floor.  Looking down at it, you see a perfect"+
      " reflection of everything in the room, though reversed,"+
      " of course.\n");

    add_item(({"throne", "thrones", "carnelian", "seating", "chair"}),
      "The thrones are made of a reddish chalcedony, hard"+
      " and crystalline. They are ornately carved with odd"+
      " repeating swirls and inlaid with gemstones. None of"+
      " them appears to be very comfortable for seating.\n");

    add_item(({"walls", "walls", "painting", "paintings", "sculpture",
	"sculptures"}),
      "The quality of the work leads you to believe each item"+
      " was made by skilled elven artisans. Each object draws "+
      " your eyes to it, and, at a loss for what to do, you try"+
      " to avoid looking too closely at any one of them.\n");

    set_noshow_obvious(1);
    add_exit("/d/Avenir/private/meeting", "meet");
    add_exit("/d/Avenir/common/outpost/bridge","bridge");
    add_exit("/d/Avenir/common/bazaar/extr/hill","bazaar");
    add_exit("/d/Avenir/common/dark/l1/stair4","stair");
    add_exit("/d/Avenir/common/dark/l2/center","dark2");
    add_exit("/d/Avenir/common/dark/l3/center","dark3");
    add_exit("/d/Avenir/common/dark/l4/center","dark4");
    add_exit("/d/Avenir/common/dark/l5/center","dark5");
    add_exit("/d/Avenir/common/bath/pub_bath","bath");
    add_exit("/d/Avenir/common/dark/lair/lair","lair");
    add_exit("/d/Avenir/common/park/s_path6","park");          
    add_exit("/d/Avenir/common/port/pub","port");
    add_exit("/d/Genesis/wiz/virtual","virtual");

    setuid();
    seteuid(getuid());

//    object board = clone_object("/d/Avenir/log/dboard");
//    board->move(this_object());
}
