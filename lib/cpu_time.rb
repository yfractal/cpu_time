# frozen_string_literal: true

require_relative "cpu_time/version"
require "cpu_time/cpu_time"

module CPUTime
  def self.time
    CPUTimeTimer.cpu_time
  end
end

module Kernel
  if method_defined?(:cpu_time)
    puts "cpu_time has been defined, please use CPUTime.time"
  else
    def cpu_time
      CPUTimeTimer.cpu_time
    end
  end
end
