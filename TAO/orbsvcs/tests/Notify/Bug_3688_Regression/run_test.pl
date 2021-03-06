eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$status = 0;
$debug_level = '0';

my $persistent_test = 0;
my $svcconf = "";
my $consumer_runtime = 10;

foreach $i (@ARGV) {
    if ($i eq '-debug') {
        $debug_level = '10';
    }
}

my $server1 = PerlACE::TestTarget::create_target (1) || die "Create target 1 failed\n";
my $server2 = PerlACE::TestTarget::create_target (2) || die "Create target 2 failed\n";
my $client = PerlACE::TestTarget::create_target (3) || die "Create target 3 failed\n";

my $ior1file = "ecf.ior";

#Files which used by server1
my $server1_ior1file = $server1->LocalFile ($ior1file);
$server1->DeleteFile($ior1file);

$hostname = $server1->HostName ();
$port = $server1->RandomPort ();

$SV1 = $server1->CreateProcess ("../../../Notify_Service/tao_cosnotification",
                              "-ORBdebuglevel $debug_level " .
                              "-NoNameSvc -IORoutput $server1_ior1file $svcconf " .
                              "-ORBEndpoint iiop://$hostname:$port");

$SV2 = $server2->CreateProcess ("supplier",
                              "-ORBdebuglevel $debug_level " .
                              "NotifyService=iioploc://$hostname:$port/NotifyService");

$CL = $client->CreateProcess ("consumer",
                              "-ORBdebuglevel $debug_level " .
                              "NotifyService=iioploc://$hostname:$port/NotifyService " .
                              "-t $consumer_runtime");


print "\n*********** Starting the Notify Service  ***********\n\n";
print $SV1->CommandLine ()."\n";

$server_status = $SV1->Spawn ();

if ($server_status != 0) {
    print STDERR "ERROR: server returned $server_status\n";
    exit 1;
}

if ($server1->WaitForFileTimed ($ior1file,
                               $server1->ProcessStartWaitInterval()) == -1) {
    print STDERR "ERROR: cannot find file <$server1_ior1file>\n";
    $SV1->Kill (); $SV1->TimedWait (1);
    exit 1;
}

print "\n*********** Starting the notification Consumer ***********\n\n";
print STDERR $SV2->CommandLine (). "\n";

$server_status = $SV2->Spawn ();

if ($server_status != 0) {
    print STDERR "ERROR: server returned $server_status\n";
    exit 1;
}

sleep ($server1->ProcessStartWaitInterval() / 3);


print "\n*********** Starting the notification Supplier ***********\n\n";
print STDERR $CL->CommandLine (). "\n";

$client_status = $CL->SpawnWaitKill ($client->ProcessStartWaitInterval());

if ($client_status != 0) {
    print STDERR "ERROR: client returned $client_status\n";
    $status = 1;
}

$server_status = $SV2->WaitKill ($server2->ProcessStopWaitInterval());

if ($server_status != 0) {
    print STDERR "ERROR: server returned $server_status\n";
    $status = 1;
}

$SV1-> Kill ();

$server1->DeleteFile($ior1file);

exit $status;
