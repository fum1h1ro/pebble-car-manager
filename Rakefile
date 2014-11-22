require 'rake/clean'

PEBBLE = 'pebble'
ADDRESS = ENV['ADDRESS']
CLEAN.include('build')

task :default => [ :run ]

task :run => [ :build, :install, :logs ]
task :build do |t|
  sh "#{PEBBLE} build"
end
task :install do |t|
  sh "#{PEBBLE} install --phone #{ADDRESS}"
end
task :logs do |t|
  sh "#{PEBBLE} logs --phone #{ADDRESS}"
end
