# frozen_string_literal: true

require "bundler/gem_tasks"
require "rspec/core/rake_task"
require "rake/extensiontask"

RSpec::Core::RakeTask.new(:spec)

Rake::ExtensionTask.new('cpu_time') do |ext|
    ext.lib_dir = 'lib/cpu_time'
end

task default: :spec
