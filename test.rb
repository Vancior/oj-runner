require 'oj_runner'
puts OjRunner.run({'cmd' => ['ls', '-l', '.'], 'timelimit' => 2000, 'memorylimit' => 65535})
