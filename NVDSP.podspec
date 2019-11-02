Pod::Spec.new do |s|
  s.name           = 'NVDSP'
  s.version        = '0.0.3'
  s.summary        = 'High-performance DSP for audio on iOS and OSX with Novocaine.'
  s.license        = { :type => 'MIT', :file => 'license.txt' }
  s.homepage       = 'https://github.com/bartolsthoorn/NVDSP'
  s.authors        = {'Bart Olsthoorn' => 'bartolsthoorn@gmail.com'}
  s.source         = { :git => 'https://github.com/leshkoapps/NVDSP.git', :tag => s.version.to_s  }
  s.source_files   = '*.{h,mm,c}', 'Filters', 'Utilities'
  s.ios.framework  = 'Foundation'
  s.ios.framework  = 'Accelerate'
  s.dependency     'Novocaine'
  s.platform       = :ios
  s.libraries    = 'stdc++'
  s.ios.deployment_target = '9.0'
end
