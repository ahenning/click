// -*- mode: c++; c-basic-offset: 4 -*-
#ifndef CLICK_TIMEFILTER_HH
#define CLICK_TIMEFILTER_HH
#include <click/element.hh>

/*
=c

TimeFilter(I<KEYWORDS>)

=s

filter packets by timestamp

=d

TimeFilter passes packets through only if they lie within a timestamp range.
You can specify that range absolutely or relative to the first timestamp
TimeFilter sees.

Keyword arguments are:

=over 8

=item START I<T>

I<T> is absolute time in seconds since the epoch. Output packets with
timestamps at least I<T>.

=item START_AFTER I<T>

I<T> is relative time in seconds (or use suffixes like `ms', `hr'). Output
packets with timestamps at least I<T> seconds after the first packet seen.

=item END I<T>

I<T> is absolute time. Output packets with timestamps up to I<T>.

=item END_AFTER I<T>

I<T> is relative time. Output packets with timestamps up to I<T> seconds after
the first packet seen.

=item INTERVAL I<T>

I<T> is relative time. Output packets for I<T> seconds after the start time,
as specified by START or START_AFTER.

=item STOP

Boolean. If true, stop the driver once the end time is exceeded. Default is
false.

=back

Supply at most one of START and START_AFTER, and at most one of END,
END_AFTER, and INTERVAL.

=a

SetTimestamp */

class TimeFilter : public Element { public:

    TimeFilter();
    ~TimeFilter();

    const char *class_name() const	{ return "TimeFilter"; }
    const char *processing() const	{ return "a/ah"; }
    TimeFilter *clone() const		{ return new TimeFilter; }

    void notify_noutputs(int);
    int configure(const Vector<String> &, ErrorHandler *);

    Packet *simple_action(Packet *);
    
  private:

    struct timeval _first;
    struct timeval _last;
    
    bool _ready : 1;
    bool _first_relative : 1;
    bool _last_relative : 1;
    bool _last_interval : 1;
    bool _stop : 1;

    void first_packet(const struct timeval &);
    Packet *kill(Packet *);
    
};

#endif
