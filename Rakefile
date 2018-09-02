require 'bundler/gem_tasks'
require 'rspec/core/rake_task'
require 'rake/extensiontask'

desc 'oj_runner test suite'
RSpec::Core::RakeTask.new(:spec) do |t|
    t.pattern = 'spec/*_spec.rb'
    t.verbose = true
end

gemspec = Gem::Specification.load('oj_runner.gemspec')
Rake::ExtensionTask.new do |ext|
    ext.name = 'oj_runner'
    ext.source_pattern = '*.{c,h}'
    ext.ext_dir = 'ext/oj_runner'
    ext.lib_dir = 'lib/oj_runner'
    ext.gem_spec = gemspec
end

task :default => [:compile, :spec]