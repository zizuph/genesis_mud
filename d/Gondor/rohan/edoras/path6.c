inherit "/d/Gondor/common/lib/town";
create_room() {
     hillside="south";
     height=3;
     road=1;
     density=1;
     extraline="When you look over the field to the north you see the Meduseld, with its golden roof, the palace where the King of Rohan lives. Kingsroad continues up towards the northeast and down towards the northwest. ";
   make_the_room();
  add_exit("/d/Gondor/rohan/edoras/path7","northeast",0);
  add_exit("/d/Gondor/rohan/edoras/path5","northwest",0);
}
