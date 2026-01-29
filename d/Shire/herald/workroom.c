inherit "/d/Shire/std/workroom";




void
create_shire_workroom()
{

    set_short("Under a sprawling oak tree");
    set_long("Thick gnarled branches loom over you "+
      "here, as the mighty oak tree sprawls above you. "+
      "Against the massive trunk sits a carved white "+
      "bench, and on closer inspection, you believe this "+
      "is a huge ivory tusk, with the seat cut "+
      "into the surface, and piles of brightly coloured "+
      "cushions making it seem comfortable indeed. \n"+
      "Here Jaypeg sits with his pipe, thinking, "+
      "pondering, dreaming up new ideas to thwart the fell "+
      "forces of Evil. Along the bark of the tree you see "+
      "knots and hollows that would seem to make perfect "+
      "footholds for one to scramble up the tree. A large "+
      "hollow appears behind the bench in the thick trunk, "+
      "apparently allowing one to go down into the roots "+
      "of the massive tree. Further around the trunk you "+
      "can make out 3 shimmering portals. \n" );


    add_item(({"tree", "oak", "branches"}), "This tree is "+
      "ancient and enormous beyond imagining, the reach "+
      "of its branches exceeding by far its towering "+
      "height. Like most things in Emerald, it exudes "+
      "a magical aura, in this case it is an aura of "+
      "peaceful comfort. Gentle, warm sunlight filters "+
      "through the multituitous branches, caressing the "+
      "the area with a relaxing glow.\n" );
    add_item(({"hollows", "foothold", "footholds", "knots" }),
      "You can make out several closely-spaced knots "+
      "and hollows along the gnarled bark of the oak, "+
      "probably allowing quick and easy access up the "+
      "trunk, into the branches above.\n" );
    add_item(({"hollow", "large hollow", "down" }), "Behind "+
      "the ivory bench you can see a large, natural "+
      "hollow in the tree, and you think you can make "+
      "out roots allowing you to step down into the trunk "+
      "without too much difficulty.\n" );
    add_item(({"portal", "portals" }), "Further around the "+
      "bole of the trunk there are three shimmering "+
      "portals, each marked with a plaque of either; "+
      "Emerald, Jasmine or Kieryn.\n" );

    add_exit("/d/Shire/jaypeg/trunk", "up", 0);
    add_exit("/d/Shire/jaypeg/roots", "down", 0);
    add_exit("/d/Shire/private/me_private", "MEPrivate", 0);

}
