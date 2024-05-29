# frozen_string_literal: true

RSpec.describe CPUTime do
  it 'it only counts cpu time' do
    t0 = cpu_time
    sleep 0.1
    t1 = cpu_time

    expect(t1 - t0).to be > 0
    expect(t1 - t0).to be < 0.1
  end
end
