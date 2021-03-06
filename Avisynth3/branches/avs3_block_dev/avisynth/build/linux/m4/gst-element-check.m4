dnl Perform a check for a GStreamer element using gst-inspect
dnl Thomas Vander Stichele <thomas at apestaart dot org>
dnl Last modification: 25/01/2005
dnl
dnl Modified by Vincent Torri <vtorri at univ-evry dot fr>
dnl Last modification: 19/10/2005

dnl AM_GST_ELEMENT_CHECK(ELEMENT-NAME, ACTION-IF-FOUND, ACTION-IF-NOT-FOUND)

AC_DEFUN([AM_GST_ELEMENT_CHECK],
[
  if test "x$GST_INSPECT" == "x"; then
    AC_CHECK_PROGS(GST_INSPECT, gst-inspect, gst-inspect-0.10, [])
  fi

  if test "x$GST_INSPECT" != "x"; then
    AC_MSG_CHECKING(GStreamer element $1 with $GST_INSPECT)
    if [ $GST_INSPECT $1 > /dev/null 2> /dev/null ]; then
      AC_MSG_RESULT(found.)
      m4_if([$2], [], [:], [$2])
    else
      AC_MSG_RESULT(not found.)
      m4_if([$3], [], [:], [$3])
    fi
  fi
])
