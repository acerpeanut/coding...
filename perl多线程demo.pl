#!/usr/bin/perl

use threads;
use threads::shared;
use strict;
use warnings;

my $check_interval = 1;
my @listTask = 1 .. 100;
my $tatolSleep :shared = 0;

sub thread_run {
	my ($dirname, $url) = @_;
	my $thread_id = threads->tid();
	print("($thread_id)\tthread_run $dirname, $url\n");

	# 在这里实现单个线程的内容
	my $range = 10;

	my $num = rand($range);
	$tatolSleep += $num;
	print("sleep($num)\n");
	sleep($num);
}

sub joinFinished {
	my @joinables = threads->list(threads::joinable);
	foreach (@joinables) {
		my $thread_id = $_->tid();
		print("$thread_id->join()\n");
		$_->join();
	}
}

my $startTime = time();
while(1) {
	my $suplement = @listTask;
	if ($suplement > 0) {
		joinFinished;

		my $thread_count = threads->list();
		if ($thread_count >= 5) {
			sleep($check_interval);
			next;
		}

		shift @listTask;

		my $thrl = threads->create(\&thread_run, "hello", "hi");
	} else {
		joinFinished;

		my $thread_count = threads->list();
		if ($thread_count >= 1) {
			sleep($check_interval);
			next;
		}
		last;
	}
}
my $endTime = time();
print("经历时间：".($endTime-$startTime)."\n"."总共睡眠：".$tatolSleep."\n");
