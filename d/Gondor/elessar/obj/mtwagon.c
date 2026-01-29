inherit "/d/Gondor/elessar/lib/wagon";

create_object()
{
  seteuid(getuid(this_object()));
  set_horses(2);
  set_name("wagon");
  add_name("carriage");
  add_name("horse carriage");
  add_name("minas_edoras_wagon");
  set_tour_file("/d/Gondor/elessar/misc/minasedoras");
  set_wagon_inside("/d/Gondor/elessar/misc/mtinwagon");
  set_max_horses(4);
  set_max_livings(4);
  make_wagon();
}
