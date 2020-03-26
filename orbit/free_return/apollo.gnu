set terminal png
#
set output "speed.png"
set size nosquare
plot "orbit.txt" u 2:5 w l title "v_mx","orbit.txt" u 2:6 w l title "v_my","orbit.txt" u 2:7 w l title "v_mmag",0 w l ls 0 notitle, "apollo.txt" u 2:5 w l title "v_ax", "apollo.txt" u 2:6 w l title "v_ay", "apollo.txt" u 2:7 w l title "v_amag", 0 w l ls 0 notitle
#
set output "distance.png"
set size nosquare
plot "orbit.txt" u 2:8 w l title "r_m", 6.371e+6 w l ls 0 title "R_m", "apollo.txt" u 2:8 w l title "r_a", 6.371e+6 w l ls 0 title "R_a"
#
set output "orbit.png"
set size square
set xrange[-4.0e8:4.0e8]
set yrange[-4.0e8:4.0e8]
plot "earth.txt" w l notitle, "orbit.txt" u 3:4 w l notitle, "apollo.txt" u 3:4 w l notitle
#
