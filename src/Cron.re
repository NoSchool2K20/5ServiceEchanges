/*open BsCron
 
// Make a job that will fire every second when started
let job =
  CronJob.make(
    `CronString("* * * * * *"),
    _ => Js.log("Just doing my job"),
    (),
  );
 
// Firing every second, printing 'Just doing my job'
start(job);*/

