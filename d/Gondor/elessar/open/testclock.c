inherit "/std/object";
string date,daytime;
object clock;

create_object() {
  set_name("clock");
  set_short("test-clock");
  set_long("A clock to test the aspects of night and day.\n"+
  "To see what time it is in Middle Earth, do 'time'\n"+
  "(c) Elessar 11/10-91\n");
}

init() {
  add_action("checktime","time",0);
}

checktime() {
  clock = find_object("/d/Gondor/elessar/lib/clock");
  daytime = clock->query_time_of_day();
  date = clock->query_date_b();
  write("The clock shows that it is now "+daytime+" in Middle Earth.\n");
  write(date);
if (clock->query_war()>0) write("The War of the Rings has begun!\n");
  return 1;
}
