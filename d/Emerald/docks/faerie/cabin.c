inherit "/d/Genesis/ship/cabin";

void
create_cabin()
{
    set_short("A warm and cosy cabin inside the incredible ship");
    set_long("   This cabin is warm and cosy and indeed a good "+
      "place to ride out the sometimes bad weather of the seas. You "+
      "feel very secure here. There's a small table with some maps and "+
      "the whole room is illuminated by a lantern in the ceiling.\n\n");

    add_item("lantern", "The lantern is secured in the ceiling. "+
      "It is a large and probably very expensive brass lantern with an "+
      "oil container that should last quite a while.\n");
    add_item(({"table", "mahogany table"}), "Like so many other "+
      "things on this ship, the table is made out of finest mahogany "+
      "despite its small size but it has some faintly visible marks "+
      "and scratches upon its formerly polished surface, indicating "+
      "that it is frequently used. On the table are some maps.\n");
    add_item(({"map", "maps"}), "The maps are nautical maps and "+
      "there seem to be several doublets, some being riddled with marks "+
      "lines and notations while others seem brand new. Alas, you find "+
      "no treasure map.\n");
    add_exit("deck", "fore");
}
